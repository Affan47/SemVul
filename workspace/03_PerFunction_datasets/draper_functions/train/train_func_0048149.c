H5Adelete_by_idx(hid_t loc_id, const char *obj_name, H5_index_t idx_type,
    H5_iter_order_t order, hsize_t n, hid_t lapl_id)
{
    H5G_loc_t	loc;
    H5G_loc_t   obj_loc;
    H5G_name_t  obj_path;
    H5O_loc_t   obj_oloc;
    hbool_t     loc_found = FALSE;
    herr_t	ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE6("e", "i*sIiIohi", loc_id, obj_name, idx_type, order, n, lapl_id);


    if(H5I_ATTR == H5I_get_type(loc_id))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "location is not valid for an attribute")
    if(H5G_loc(loc_id, &loc) < 0)
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a location")
    if(!obj_name || !*obj_name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no object name")
    if(idx_type <= H5_INDEX_UNKNOWN || idx_type >= H5_INDEX_N)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid index type specified")
    if(order <= H5_ITER_UNKNOWN || order >= H5_ITER_N)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid iteration order specified")
    if(H5P_DEFAULT == lapl_id)
        lapl_id = H5P_LINK_ACCESS_DEFAULT;
    else
        if(TRUE != H5P_isa_class(lapl_id, H5P_LINK_ACCESS))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not link access property list ID")


    obj_loc.oloc = &obj_oloc;
    obj_loc.path = &obj_path;
    H5G_loc_reset(&obj_loc);


    if(H5G_loc_find(&loc, obj_name, &obj_loc, lapl_id, H5AC_dxpl_id) < 0)
        HGOTO_ERROR(H5E_ATTR, H5E_NOTFOUND, FAIL, "object not found")
    loc_found = TRUE;


    if(H5O_attr_remove_by_idx(obj_loc.oloc, idx_type, order, n, H5AC_dxpl_id) < 0)
        HGOTO_ERROR(H5E_ATTR, H5E_CANTDELETE, FAIL, "unable to delete attribute")

done:

    if(loc_found && H5G_loc_free(&obj_loc) < 0)
        HDONE_ERROR(H5E_ATTR, H5E_CANTRELEASE, FAIL, "can't free location")

    FUNC_LEAVE_API(ret_value)
}
