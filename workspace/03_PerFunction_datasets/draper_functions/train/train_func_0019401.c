H5Pget_local_heap_size_hint(hid_t plist_id, size_t *size_hint )
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE2("e", "ix", plist_id, size_hint);

    if(size_hint) {
        H5P_genplist_t *plist;
        H5O_ginfo_t ginfo;


        if(NULL == (plist = H5P_object_verify(plist_id, H5P_GROUP_CREATE)))
            HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, FAIL, "can't find object for ID")


        if(H5P_get(plist, H5G_CRT_GROUP_INFO_NAME, &ginfo) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get group info")


        *size_hint = ginfo.lheap_size_hint;
    }

done:
    FUNC_LEAVE_API(ret_value)
}
