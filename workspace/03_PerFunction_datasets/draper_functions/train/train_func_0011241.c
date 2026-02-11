H5B2_get_node_info_test(H5B2_t *bt2, hid_t dxpl_id, void *udata,
    H5B2_node_info_test_t *ninfo)
{
    H5B2_hdr_t	*hdr;
    H5B2_node_ptr_t curr_node_ptr;
    unsigned    depth;
    int         cmp;
    unsigned    idx;
    herr_t	ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    HDassert(bt2);


    bt2->hdr->f = bt2->f;


    hdr = bt2->hdr;


    curr_node_ptr = hdr->root;


    depth = hdr->depth;


    if(0 == curr_node_ptr.node_nrec)
        HGOTO_ERROR(H5E_BTREE, H5E_NOTFOUND, FAIL, "B-tree has no records")


    cmp = -1;
    while(depth > 0 && cmp != 0) {
        H5B2_internal_t *internal;
        H5B2_node_ptr_t next_node_ptr;


        if(NULL == (internal = H5B2_protect_internal(hdr, dxpl_id, curr_node_ptr.addr, curr_node_ptr.node_nrec, depth, H5AC_READ)))
            HGOTO_ERROR(H5E_BTREE, H5E_CANTPROTECT, FAIL, "unable to load B-tree internal node")


        if(H5B2_locate_record(hdr->cls, internal->nrec, hdr->nat_off, internal->int_native,
                               udata, &idx, &cmp) < 0)
            HGOTO_ERROR(H5E_BTREE, H5E_CANTCOMPARE, FAIL, "can't compare btree2 records")

        if(cmp > 0)
            idx++;

        if(cmp != 0) {

            next_node_ptr = internal->node_ptrs[idx];


            if(H5AC_unprotect(hdr->f, dxpl_id, H5AC_BT2_INT, curr_node_ptr.addr, internal, H5AC__NO_FLAGS_SET) < 0)
                HGOTO_ERROR(H5E_BTREE, H5E_CANTUNPROTECT, FAIL, "unable to release B-tree node")


            curr_node_ptr = next_node_ptr;
        }
        else {

            if(H5AC_unprotect(hdr->f, dxpl_id, H5AC_BT2_INT, curr_node_ptr.addr, internal, H5AC__NO_FLAGS_SET) < 0)
                HGOTO_ERROR(H5E_BTREE, H5E_CANTUNPROTECT, FAIL, "unable to release B-tree node")


            ninfo->depth = depth;
            ninfo->nrec = curr_node_ptr.node_nrec;


            HGOTO_DONE(SUCCEED)
        }


        depth--;
    }

    {
        H5B2_leaf_t *leaf;


        if(NULL == (leaf = H5B2_protect_leaf(hdr, dxpl_id, curr_node_ptr.addr, curr_node_ptr.node_nrec, H5AC_READ)))
            HGOTO_ERROR(H5E_BTREE, H5E_CANTPROTECT, FAIL, "unable to protect B-tree leaf node")


        if(H5B2_locate_record(hdr->cls, leaf->nrec, hdr->nat_off, leaf->leaf_native,
                               udata, &idx, &cmp) < 0)
            HGOTO_ERROR(H5E_BTREE, H5E_CANTCOMPARE, FAIL, "can't compare btree2 records")


        if(H5AC_unprotect(hdr->f, dxpl_id, H5AC_BT2_LEAF, curr_node_ptr.addr, leaf, H5AC__NO_FLAGS_SET) < 0)
            HGOTO_ERROR(H5E_BTREE, H5E_CANTUNPROTECT, FAIL, "unable to release B-tree node")


        if(cmp != 0)
            HGOTO_ERROR(H5E_BTREE, H5E_NOTFOUND, FAIL, "record not in B-tree")
    }


    ninfo->depth = depth;
    ninfo->nrec = curr_node_ptr.node_nrec;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
