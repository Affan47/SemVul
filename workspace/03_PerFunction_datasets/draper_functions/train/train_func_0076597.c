H5Glink(hid_t cur_loc_id, H5G_link_t type, const char *cur_name, const char *new_name)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE4("e", "iLl*s*s", cur_loc_id, type, cur_name, new_name);


    if(!cur_name || !*cur_name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no current name specified")
    if(!new_name || !*new_name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no new name specified")

    if(type == H5L_TYPE_HARD) {
        if((ret_value = H5G_link_hard(cur_loc_id, cur_name, H5L_SAME_LOC, new_name)) < 0)
            HGOTO_ERROR(H5E_LINK, H5E_CANTINIT, FAIL, "couldn't create link")
    }
    else if(type == H5L_TYPE_SOFT) {
        H5G_loc_t	cur_loc;


        if(H5G_loc(cur_loc_id, &cur_loc) < 0)
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a location")


        if(H5L_create_soft(cur_name, &cur_loc, new_name, H5P_DEFAULT, H5P_DEFAULT, H5AC_dxpl_id) < 0)
            HGOTO_ERROR(H5E_LINK, H5E_CANTINIT, FAIL, "unable to create link")
    }
    else
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "Not a valid link type")

done:
    FUNC_LEAVE_API(ret_value)
}
