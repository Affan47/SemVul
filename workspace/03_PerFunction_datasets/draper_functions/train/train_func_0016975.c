H5B2_neighbor(H5B2_t *bt2, hid_t dxpl_id, H5B2_compare_t range, void *udata,
    H5B2_found_t op, void *op_data)
{
    H5B2_hdr_t	*hdr;
    herr_t	ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5B2_neighbor, FAIL)


    HDassert(bt2);
    HDassert(op);


    bt2->hdr->f = bt2->f;


    hdr = bt2->hdr;


    if(!H5F_addr_defined(hdr->root.addr))
        HGOTO_ERROR(H5E_BTREE, H5E_NOTFOUND, FAIL, "B-tree has no records")


    if(hdr->depth > 0) {
        if(H5B2_neighbor_internal(hdr, dxpl_id, hdr->depth, &hdr->root, NULL, range, udata, op, op_data) < 0)
            HGOTO_ERROR(H5E_BTREE, H5E_NOTFOUND, FAIL, "unable to find neighbor record in B-tree internal node")
    }
    else {
        if(H5B2_neighbor_leaf(hdr, dxpl_id, &hdr->root, NULL, range, udata, op, op_data) < 0)
            HGOTO_ERROR(H5E_BTREE, H5E_NOTFOUND, FAIL, "unable to find neighbor record in B-tree leaf node")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
