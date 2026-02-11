H5Pget_cache(hid_t plist_id, int *mdc_nelmts,
	     size_t *rdcc_nslots, size_t *rdcc_nbytes, double *rdcc_w0)
{
    H5P_genplist_t *plist;
    herr_t ret_value=SUCCEED;

    FUNC_ENTER_API(H5Pget_cache, FAIL);
    H5TRACE5("e", "i*Is*z*z*d", plist_id, mdc_nelmts, rdcc_nslots, rdcc_nbytes,
             rdcc_w0);


    if(NULL == (plist = H5P_object_verify(plist_id,H5P_FILE_ACCESS)))
        HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, FAIL, "can't find object for ID");


    if (mdc_nelmts)
        *mdc_nelmts = 0;

    if (rdcc_nslots)
        if(H5P_get(plist, H5F_ACS_DATA_CACHE_NUM_SLOTS_NAME, rdcc_nslots) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTGET,FAIL, "can't get data cache number of slots");
    if (rdcc_nbytes)
        if(H5P_get(plist, H5F_ACS_DATA_CACHE_BYTE_SIZE_NAME, rdcc_nbytes) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTGET,FAIL, "can't get data cache byte size");
    if (rdcc_w0)
        if(H5P_get(plist, H5F_ACS_PREEMPT_READ_CHUNKS_NAME, rdcc_w0) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTGET,FAIL, "can't get preempt read chunks");

done:
    FUNC_LEAVE_API(ret_value);
}
