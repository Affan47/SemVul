H5Lget_info(hid_t loc_id, const char *name, H5L_info_t *linfo ,
    hid_t lapl_id)
{
    H5G_loc_t	loc;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE4("e", "i*sxi", loc_id, name, linfo, lapl_id);


    if(H5G_loc(loc_id, &loc))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a location")
    if(!name || !*name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no name specified")
    if(H5P_DEFAULT == lapl_id)
        lapl_id = H5P_LINK_ACCESS_DEFAULT;
    else
        if(TRUE != H5P_isa_class(lapl_id, H5P_LINK_ACCESS))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not link access property list ID")


    if(H5L_get_info(&loc, name, linfo, lapl_id, H5AC_ind_dxpl_id) < 0)
	HGOTO_ERROR(H5E_SYM, H5E_NOTFOUND, FAIL, "unable to get link info")

done:
    FUNC_LEAVE_API(ret_value)
}
