H5Pget_libver_bounds(hid_t plist_id, H5F_libver_t *low,
    H5F_libver_t *high)
{
    H5P_genplist_t *plist;
    hbool_t latest;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE3("e", "ixx", plist_id, low, high);


    if(NULL == (plist = H5P_object_verify(plist_id, H5P_FILE_ACCESS)))
        HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, FAIL, "can't find object for ID")


    if(H5P_get(plist, H5F_ACS_LATEST_FORMAT_NAME, &latest) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get library version bounds")


    if(low)
        *low = latest ? H5F_LIBVER_LATEST : H5F_LIBVER_EARLIEST;
    if(high)
        *high = H5F_LIBVER_LATEST;

done:
    FUNC_LEAVE_API(ret_value)
}
