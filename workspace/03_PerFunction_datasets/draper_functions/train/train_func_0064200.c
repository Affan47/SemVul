H5I_get_file_id(hid_t obj_id, hbool_t app_ref)
{
    H5I_type_t type;
    hid_t ret_value;

    FUNC_ENTER_NOAPI_NOINIT(H5I_get_file_id)


    type = H5I_TYPE(obj_id);
    if(type == H5I_FILE) {

        if(H5I_inc_ref(obj_id, app_ref) < 0)
            HGOTO_ERROR(H5E_ATOM, H5E_CANTSET, FAIL, "incrementing file ID failed")


        ret_value = obj_id;
    }
    else if(type == H5I_DATATYPE || type == H5I_GROUP || type == H5I_DATASET || type == H5I_ATTR) {
        H5G_loc_t loc;


        if(H5G_loc(obj_id, &loc) < 0)
            HGOTO_ERROR(H5E_ATOM, H5E_CANTGET, FAIL, "can't get object location")


        if((ret_value = H5F_get_id(loc.oloc->file, app_ref)) < 0)
            HGOTO_ERROR(H5E_ATOM, H5E_CANTGET, FAIL, "can't get file ID")
    }
    else
        HGOTO_ERROR(H5E_ARGS, H5E_BADRANGE, FAIL, "invalid object ID")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
