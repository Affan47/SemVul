H5Pset_obj_track_times(hid_t plist_id, hbool_t track_times)
{
    H5P_genplist_t *plist;
    uint8_t ohdr_flags;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(H5Pset_obj_track_times, FAIL)
    H5TRACE2("e", "ib", plist_id, track_times);


    if(NULL == (plist = H5P_object_verify(plist_id, H5P_OBJECT_CREATE)))
        HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, FAIL, "can't find object for ID")


    if(H5P_get(plist, H5O_CRT_OHDR_FLAGS_NAME, &ohdr_flags) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get object header flags")


    ohdr_flags &= (uint8_t)~H5O_HDR_STORE_TIMES;


    ohdr_flags |= (uint8_t)(track_times ? H5O_HDR_STORE_TIMES : 0);


    if(H5P_set(plist, H5O_CRT_OHDR_FLAGS_NAME, &ohdr_flags) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTSET, FAIL, "can't set object header flags")

done:
    FUNC_LEAVE_API(ret_value)
}
