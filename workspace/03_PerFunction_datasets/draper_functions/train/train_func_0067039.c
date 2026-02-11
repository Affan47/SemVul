H5Sdecode(const void *buf)
{
    H5S_t       *ds;
    hid_t       ret_value;

    FUNC_ENTER_API(FAIL)
    H5TRACE1("i", "*x", buf);

    if(buf == NULL)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "empty buffer")

    if((ds = H5S_decode((const unsigned char *)buf)) == NULL)
	HGOTO_ERROR(H5E_DATASPACE, H5E_CANTDECODE, FAIL, "can't decode object")


    if((ret_value = H5I_register(H5I_DATASPACE, ds, TRUE)) < 0)
	HGOTO_ERROR(H5E_DATASPACE, H5E_CANTREGISTER, FAIL, "unable to register dataspace")

done:
    FUNC_LEAVE_API(ret_value)
}
