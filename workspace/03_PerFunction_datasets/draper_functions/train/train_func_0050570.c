H5B2_neighbor_leaf(H5B2_hdr_t *hdr, hid_t dxpl_id, H5B2_node_ptr_t *curr_node_ptr,
    void *neighbor_loc, H5B2_compare_t comp, void *udata, H5B2_found_t op,
    void *op_data)
{
    H5B2_leaf_t *leaf;
    unsigned    idx;
    int         cmp = 0;
    herr_t	ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(hdr);
    HDassert(curr_node_ptr);
    HDassert(H5F_addr_defined(curr_node_ptr->addr));
    HDassert(op);


    if(NULL == (leaf = H5B2_protect_leaf(hdr, dxpl_id, curr_node_ptr->addr, curr_node_ptr->node_nrec, H5AC_READ)))
        HGOTO_ERROR(H5E_BTREE, H5E_CANTPROTECT, FAIL, "unable to protect B-tree leaf node")


    cmp = H5B2_locate_record(hdr->cls, leaf->nrec, hdr->nat_off, leaf->leaf_native, udata, &idx);
    if(cmp > 0)
        idx++;
    else
        if(cmp == 0 && comp == H5B2_COMPARE_GREATER)
            idx++;


    if(comp == H5B2_COMPARE_LESS) {
        if(idx > 0)
            neighbor_loc = H5B2_LEAF_NREC(leaf, hdr, idx - 1);
    }
    else {
        HDassert(comp == H5B2_COMPARE_GREATER);

        if(idx < leaf->nrec)
            neighbor_loc = H5B2_LEAF_NREC(leaf, hdr, idx);
    }


    if(neighbor_loc) {

        if((op)(neighbor_loc, op_data) < 0)
            HGOTO_ERROR(H5E_BTREE, H5E_NOTFOUND, FAIL, "'found' callback failed for B-tree neighbor operation")
    }
    else
        HGOTO_ERROR(H5E_BTREE, H5E_NOTFOUND, FAIL, "unable to find neighbor record in B-tree")

done:

    if(leaf && H5AC_unprotect(hdr->f, dxpl_id, H5AC_BT2_LEAF, curr_node_ptr->addr, leaf, H5AC__NO_FLAGS_SET) < 0)
        HDONE_ERROR(H5E_BTREE, H5E_CANTUNPROTECT, FAIL, "unable to release B-tree leaf node")

    FUNC_LEAVE_NOAPI(ret_value)
}
