H5B2_size(H5B2_t *bt2, hid_t dxpl_id, hsize_t *btree_size)
{
    H5B2_hdr_t	*hdr;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    HDassert(bt2);
    HDassert(btree_size);


    bt2->hdr->f = bt2->f;


    hdr = bt2->hdr;


    *btree_size += hdr->hdr_size;


    if(hdr->root.node_nrec > 0) {

        if(hdr->depth == 0)
            *btree_size += hdr->node_size;
        else

            if(H5B2_node_size(hdr, dxpl_id, hdr->depth, &hdr->root, btree_size) < 0)
                HGOTO_ERROR(H5E_BTREE, H5E_CANTLIST, FAIL, "node iteration failed")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
