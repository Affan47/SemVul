H5Gget_linkval(hid_t loc_id, const char *name, size_t size, char *buf)
{
    H5G_loc_t	loc;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE4("e", "i*szx", loc_id, name, size, buf);


    if(H5G_loc(loc_id, &loc))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a location")
    if(!name || !*name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no name specified")


    if(H5L_get_val(&loc, name, buf, size, H5P_DEFAULT, H5AC_ind_dxpl_id) < 0)
      HGOTO_ERROR(H5E_SYM, H5E_NOTFOUND, FAIL, "couldn't get link info")

done:
    FUNC_LEAVE_API(ret_value)
}
