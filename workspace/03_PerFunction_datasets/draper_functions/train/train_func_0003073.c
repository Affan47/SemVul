H5S_hyper_iter_block (const H5S_sel_iter_t *iter, hsize_t *start, hsize_t *end)
{
    unsigned u;

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5S_hyper_iter_block);


    assert (iter);
    assert (start);
    assert (end);


    if(iter->u.hyp.diminfo_valid) {

        for(u=0; u<iter->rank; u++) {
            start[u]=iter->u.hyp.off[u];
            end[u]=(start[u]+iter->u.hyp.diminfo[u].block)-1;
        }
    }
    else {

        for(u=0; u<iter->rank; u++)
            start[u]=iter->u.hyp.span[u]->low;


        for(u=0; u<iter->rank; u++)
            end[u]=iter->u.hyp.span[u]->high;
    }

    FUNC_LEAVE_NOAPI(SUCCEED);
}
