H5Iget_file_id(hid_t obj_id)
{
    hid_t ret_value;

    FUNC_ENTER_API(FAIL)
    H5TRACE1("i", "i", obj_id);

    if((ret_value = H5I_get_file_id(obj_id, TRUE)) < 0)
        HGOTO_ERROR(H5E_ATOM, H5E_CANTGET, FAIL, "can't retrieve file ID")

done:
    FUNC_LEAVE_API(ret_value)
}
