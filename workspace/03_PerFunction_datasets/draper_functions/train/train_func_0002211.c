H5F_get_objects(const H5F_t *f, unsigned types, size_t max_index, hid_t *obj_id_list, hbool_t app_ref, size_t *obj_id_count_ptr)
{
    size_t obj_id_count=0;
    H5F_olist_t olist;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(obj_id_count_ptr);


    olist.obj_id_list  = (max_index==0 ? NULL : obj_id_list);
    olist.obj_id_count = &obj_id_count;
    olist.list_index   = 0;
    olist.max_index   = max_index;


    if(types & H5F_OBJ_LOCAL) {
        olist.file_info.local = TRUE;
        olist.file_info.ptr.file = f;
    }
    else {
        olist.file_info.local = FALSE;
        olist.file_info.ptr.shared = f ? f->shared : NULL;
    }


    if(types & H5F_OBJ_FILE) {
        olist.obj_type = H5I_FILE;
        if(H5I_iterate(H5I_FILE, H5F_get_objects_cb, &olist, app_ref) < 0)
            HGOTO_ERROR(H5E_FILE, H5E_BADITER, FAIL, "iteration failed(1)")
    }


    if(types & H5F_OBJ_DATASET) {
        olist.obj_type = H5I_DATASET;
        if(H5I_iterate(H5I_DATASET, H5F_get_objects_cb, &olist, app_ref) < 0)
            HGOTO_ERROR(H5E_FILE, H5E_BADITER, FAIL, "iteration failed(2)")
    }


    if(types & H5F_OBJ_GROUP) {
        olist.obj_type = H5I_GROUP;
        if(H5I_iterate(H5I_GROUP, H5F_get_objects_cb, &olist, app_ref) < 0)
            HGOTO_ERROR(H5E_FILE, H5E_BADITER, FAIL, "iteration failed(3)")
    }


    if(types & H5F_OBJ_DATATYPE) {
        olist.obj_type = H5I_DATATYPE;
        if(H5I_iterate(H5I_DATATYPE, H5F_get_objects_cb, &olist, app_ref) < 0)
            HGOTO_ERROR(H5E_FILE, H5E_BADITER, FAIL, "iteration failed(4)")
    }


    if(types & H5F_OBJ_ATTR) {
        olist.obj_type = H5I_ATTR;
        if(H5I_iterate(H5I_ATTR, H5F_get_objects_cb, &olist, app_ref) < 0)
            HGOTO_ERROR(H5E_FILE, H5E_BADITER, FAIL, "iteration failed(5)")
    }


    *obj_id_count_ptr = obj_id_count;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
