H5Pget_istore_k(hid_t plist_id, unsigned *ik  )
{
    unsigned btree_k[H5B_NUM_BTREE_ID];
    H5P_genplist_t *plist;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE2("e", "ix", plist_id, ik);


    if(NULL == (plist = H5P_object_verify(plist_id,H5P_FILE_CREATE)))
        HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, FAIL, "can't find object for ID");


    if(ik) {
        if(H5P_get(plist, H5F_CRT_BTREE_RANK_NAME, btree_k) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get rank for btree interanl nodes");
        *ik = btree_k[H5B_CHUNK_ID];
    }

done:
    FUNC_LEAVE_API(ret_value)
}
