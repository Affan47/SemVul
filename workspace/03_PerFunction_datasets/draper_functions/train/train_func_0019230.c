H5B2_swap_leaf(H5B2_hdr_t *hdr, hid_t dxpl_id, unsigned depth,
    H5B2_internal_t *internal, unsigned *internal_flags_ptr,
    unsigned idx, void *swap_loc)
{
    const H5AC_class_t *child_class;
    haddr_t child_addr;
    void *child;
    uint8_t *child_native;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5B2_swap_leaf)


    HDassert(hdr);
    HDassert(internal);
    HDassert(internal_flags_ptr);
    HDassert(idx <= internal->nrec);


    if(depth > 1) {
        H5B2_internal_t *child_internal;


        child_class = H5AC_BT2_INT;
        child_addr = internal->node_ptrs[idx].addr;


        if(NULL == (child_internal = H5B2_protect_internal(hdr, dxpl_id, child_addr, internal->node_ptrs[idx].node_nrec, (depth - 1), H5AC_WRITE)))
            HGOTO_ERROR(H5E_BTREE, H5E_CANTPROTECT, FAIL, "unable to protect B-tree internal node")


        child = child_internal;
        child_native = child_internal->int_native;
    }
    else {
        H5B2_leaf_t *child_leaf;


        child_class = H5AC_BT2_LEAF;
        child_addr = internal->node_ptrs[idx].addr;


        if(NULL == (child_leaf = H5B2_protect_leaf(hdr, dxpl_id, child_addr, internal->node_ptrs[idx].node_nrec, H5AC_WRITE)))
            HGOTO_ERROR(H5E_BTREE, H5E_CANTPROTECT, FAIL, "unable to protect B-tree leaf node")


        child = child_leaf;
        child_native = child_leaf->leaf_native;
    }


    HDmemcpy(hdr->page, H5B2_NAT_NREC(child_native, hdr, 0), hdr->cls->nrec_size);
    HDmemcpy(H5B2_NAT_NREC(child_native, hdr, 0), swap_loc, hdr->cls->nrec_size);
    HDmemcpy(swap_loc, hdr->page, hdr->cls->nrec_size);


    *internal_flags_ptr |= H5AC__DIRTIED_FLAG;

#ifdef H5B2_DEBUG
    H5B2_assert_internal((hsize_t)0, hdr, internal);
    if(depth > 1)
        H5B2_assert_internal(internal->node_ptrs[idx].all_nrec, hdr, child);
    else
        H5B2_assert_leaf(hdr, child);
#endif

done:

    if(child && H5AC_unprotect(hdr->f, dxpl_id, child_class, child_addr, child, H5AC__DIRTIED_FLAG) < 0)
        HDONE_ERROR(H5E_BTREE, H5E_CANTUNPROTECT, FAIL, "unable to release B-tree child node")

    FUNC_LEAVE_NOAPI(ret_value)
}
