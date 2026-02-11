H5G_get_name(const H5G_loc_t *loc, char *name, size_t size,
    hbool_t *cached, hid_t lapl_id, hid_t dxpl_id)
{
    ssize_t len = 0;
    ssize_t ret_value;

    FUNC_ENTER_NOAPI(FAIL)


    HDassert(loc);


    if(loc->path->user_path_r != NULL && loc->path->obj_hidden == 0) {
        len = H5RS_len(loc->path->user_path_r);

        if(name) {
            HDstrncpy(name, H5RS_get_str(loc->path->user_path_r), MIN((size_t)(len + 1), size));
            if((size_t)len >= size)
                name[size - 1] = '\0';
        }


        if(cached)
            *cached = TRUE;
    }
    else if(!loc->path->obj_hidden) {
        hid_t	  file;


        if((file = H5F_get_id(loc->oloc->file, FALSE)) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_CANTGET, FAIL, "can't get file ID")


        if((len = H5G_get_name_by_addr(file, lapl_id, dxpl_id, loc->oloc, name, size)) < 0) {
            H5I_dec_ref(file);
            HGOTO_ERROR(H5E_SYM, H5E_CANTGET, FAIL, "can't determine name")
        }


        if(H5I_dec_ref(file) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_CANTCLOSEFILE, FAIL, "can't determine name")


        if(cached)
            *cached = FALSE;
    }


    ret_value = len;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
