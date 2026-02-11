H5Gcreate1(hid_t loc_id, const char *name, size_t size_hint)
{
    H5G_loc_t	    loc;
    H5G_t	   *grp = NULL;
    hid_t           tmp_gcpl = (-1);
    hid_t	    ret_value;

    FUNC_ENTER_API(FAIL)
    H5TRACE3("i", "i*sz", loc_id, name, size_hint);


    if(H5G_loc(loc_id, &loc) < 0)
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a location")
    if(!name || !*name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no name given")


    if(size_hint > 0) {
        H5P_genplist_t  *gc_plist;
        H5O_ginfo_t     ginfo;


        if(NULL == (gc_plist = (H5P_genplist_t *)H5I_object(H5P_GROUP_CREATE_DEFAULT)))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a property list")


        if((tmp_gcpl = H5P_copy_plist(gc_plist, FALSE)) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_CANTGET, FAIL, "unable to copy the creation property list")


        if(NULL == (gc_plist = (H5P_genplist_t *)H5I_object(tmp_gcpl)))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a property list")


        if(H5P_get(gc_plist, H5G_CRT_GROUP_INFO_NAME, &ginfo) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get group info")


        ginfo.lheap_size_hint = size_hint;
        if(H5P_set(gc_plist, H5G_CRT_GROUP_INFO_NAME, &ginfo) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTSET, FAIL, "can't set group info")
    }
    else
        tmp_gcpl = H5P_GROUP_CREATE_DEFAULT;


    if(NULL == (grp = H5G__create_named(&loc, name, H5P_LINK_CREATE_DEFAULT,
            tmp_gcpl, H5P_GROUP_ACCESS_DEFAULT, H5AC_dxpl_id)))
        HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "unable to create group")
    if((ret_value = H5I_register(H5I_GROUP, grp, TRUE)) < 0)
	HGOTO_ERROR(H5E_ATOM, H5E_CANTREGISTER, FAIL, "unable to register group")

done:
    if(tmp_gcpl > 0 && tmp_gcpl != H5P_GROUP_CREATE_DEFAULT)
        if(H5I_dec_ref(tmp_gcpl) < 0)
            HDONE_ERROR(H5E_SYM, H5E_CLOSEERROR, FAIL, "unable to release property list")

    if(ret_value < 0)
        if(grp && H5G_close(grp) < 0)
            HDONE_ERROR(H5E_SYM, H5E_CLOSEERROR, FAIL, "unable to release group")

    FUNC_LEAVE_API(ret_value)
}
