H5Iregister_type(size_t hash_size, unsigned reserved, H5I_free_t free_func)
{
    H5I_class_t *cls = NULL;
    H5I_type_t new_type;
    H5I_type_t ret_value;

    FUNC_ENTER_API(H5I_BADID)
    H5TRACE3("It", "zIux", hash_size, reserved, free_func);


    if(H5I_next_type < H5I_MAX_NUM_TYPES) {
        new_type = H5I_next_type;
        H5_INC_ENUM(H5I_type_t, H5I_next_type);
    }
    else {
        hbool_t done;
        int i;


        done = FALSE;
        for(i = H5I_NTYPES; i < H5I_MAX_NUM_TYPES && done == FALSE; i++) {
            if(NULL == H5I_id_type_list_g[i]) {

                new_type = (H5I_type_t)i;
                done = TRUE;
            }
        }


        if(done == FALSE)
            HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, H5I_BADID, "Maximum number of ID types exceeded.")
    }


    if(NULL == (cls = H5FL_MALLOC(H5I_class_t)))
        HGOTO_ERROR(H5E_ATOM, H5E_CANTALLOC, H5I_BADID, "ID class allocation failed")


    cls->type_id = new_type;
    cls->flags = H5I_CLASS_IS_APPLICATION;
    cls->hash_size = hash_size;
    cls->reserved = reserved;
    cls->free_func = free_func;


    if(H5I_register_type(cls) < 0)
        HGOTO_ERROR(H5E_ATOM, H5E_CANTINIT, H5I_BADID, "can't initialize ID class")


    ret_value = new_type;

done:

    if(ret_value < 0) {
        if(cls)
            cls = H5FL_FREE(H5I_class_t, cls);
    }

    FUNC_LEAVE_API(ret_value)
}
