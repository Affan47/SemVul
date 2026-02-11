H5Fget_obj_count(hid_t file_id, unsigned types)
{
    H5F_t    *f = NULL;
    size_t  obj_count = 0;
    ssize_t  ret_value;

    FUNC_ENTER_API(FAIL)
    H5TRACE2("Zs", "iIu", file_id, types);


    if(file_id != (hid_t)H5F_OBJ_ALL && (NULL == (f = (H5F_t *)H5I_object_verify(file_id, H5I_FILE))))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "not a file id")
    if(0 == (types & H5F_OBJ_ALL))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "not an object type")


    if(H5F_get_obj_count(f, types, TRUE, &obj_count) < 0)
	HGOTO_ERROR(H5E_INTERNAL, H5E_BADITER, FAIL, "H5F_get_obj_count failed")


    ret_value = (ssize_t)obj_count;

done:
    FUNC_LEAVE_API(ret_value)
}
