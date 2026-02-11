H5Sselect_none(hid_t spaceid)
{
    H5S_t *space;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE1("e", "i", spaceid);


    if(NULL == (space = (H5S_t *)H5I_object_verify(spaceid, H5I_DATASPACE)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a data space")


    if(H5S_select_none(space) < 0)
        HGOTO_ERROR(H5E_DATASPACE, H5E_CANTDELETE, FAIL, "can't change selection")

done:
    FUNC_LEAVE_API(ret_value)
}
