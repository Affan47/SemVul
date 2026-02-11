H5S_point_get_seq_list(const H5S_t *space, unsigned flags, H5S_sel_iter_t *iter,
    size_t maxseq, size_t maxelem, size_t *nseq, size_t *nelem,
    hsize_t *off, size_t *len)
{
    size_t io_left;
    size_t start_io_left;
    H5S_pnt_node_t *node;
    hsize_t dims[H5O_LAYOUT_NDIMS];
    int	ndims;
    hsize_t	acc;
    hsize_t	loc;
    size_t      curr_seq;
    int         i;
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5S_point_get_seq_list)


    HDassert(space);
    HDassert(iter);
    HDassert(maxseq > 0);
    HDassert(maxelem > 0);
    HDassert(nseq);
    HDassert(nelem);
    HDassert(off);
    HDassert(len);


    H5_CHECK_OVERFLOW(iter->elmt_left, hsize_t, size_t);
    start_io_left = io_left = (size_t)MIN(iter->elmt_left, maxelem);


    if((ndims = H5S_get_simple_extent_dims (space, dims, NULL)) < 0)
        HGOTO_ERROR(H5E_DATASPACE, H5E_CANTINIT, FAIL, "unable to retrieve data space dimensions")


    node = iter->u.pnt.curr;
    curr_seq = 0;
    while(NULL != node) {

        for(i = ndims - 1, acc = iter->elmt_size, loc = 0; i >= 0; i--) {
            loc += (node->pnt[i] + space->select.offset[i]) * acc;
            acc *= dims[i];
        }


        if(curr_seq>0) {

            if((flags&H5S_GET_SEQ_LIST_SORTED) && loc<off[curr_seq-1])
                break;


            if(loc==(off[curr_seq-1]+len[curr_seq-1])) {

                len[curr_seq-1]+=iter->elmt_size;
            }
            else {

                off[curr_seq]=loc;
                len[curr_seq]=iter->elmt_size;


                curr_seq++;
            }
        }
        else {

            off[curr_seq]=loc;
            len[curr_seq]=iter->elmt_size;


            curr_seq++;
        }


        io_left--;


        iter->u.pnt.curr=node->next;
        iter->elmt_left--;


        if(curr_seq==maxseq)
            break;


        if(io_left==0)
            break;


        node=node->next;
      }


    *nseq=curr_seq;


    *nelem=start_io_left-io_left;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
