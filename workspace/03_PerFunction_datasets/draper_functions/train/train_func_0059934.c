H5Ldelete(hid_t loc_id, const char *name, hid_t lapl_id)
{
    H5G_loc_t	loc;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE3("e", "i*si", loc_id, name, lapl_id);


    if(H5G_loc(loc_id, &loc) < 0)
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a location")
    if(!name || !*name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no name")


    if(H5L_delete(&loc, name, lapl_id, H5AC_dxpl_id) < 0)
	HGOTO_ERROR(H5E_LINK, H5E_CANTDELETE, FAIL, "unable to delete link")

done:
    FUNC_LEAVE_API(ret_value)
}
