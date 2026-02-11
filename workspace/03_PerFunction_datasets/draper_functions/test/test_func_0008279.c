H5Lcreate_external(const char *file_name, const char *obj_name,
    hid_t link_loc_id, const char *link_name, hid_t lcpl_id, hid_t lapl_id)
{
    H5G_loc_t	link_loc;
    char       *norm_obj_name = NULL;
    void       *ext_link_buf = NULL;
    size_t      buf_size;
    uint8_t    *p;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_API(H5Lcreate_external, FAIL)
    H5TRACE6("e", "*s*si*sii", file_name, obj_name, link_loc_id, link_name,
             lcpl_id, lapl_id);


    if(!file_name || !*file_name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no file name specified")
    if(!obj_name || !*obj_name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no object name specified")
    if(H5G_loc(link_loc_id, &link_loc) < 0)
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a location")
    if(!link_name || !*link_name)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "no link name specified")


    if(NULL == (norm_obj_name = H5G_normalize(obj_name)))
        HGOTO_ERROR(H5E_SYM, H5E_BADVALUE, FAIL, "can't normalize object name")


    buf_size = 1 + (HDstrlen(file_name) + 1) + (HDstrlen(norm_obj_name) + 1);
    if(NULL == (ext_link_buf = H5MM_malloc(buf_size)))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, FAIL, "unable to allocate udata buffer")


    p = (uint8_t *)ext_link_buf;
    *p++ = (H5L_EXT_VERSION << 4) | H5L_EXT_FLAGS_ALL;
    HDstrcpy((char *)p, file_name);
    p += HDstrlen(file_name) + 1;
    HDstrcpy((char *)p, norm_obj_name);


    if(H5L_create_ud(&link_loc, link_name, ext_link_buf, buf_size, H5L_TYPE_EXTERNAL, lcpl_id, lapl_id, H5AC_dxpl_id) < 0)
        HGOTO_ERROR(H5E_LINK, H5E_CANTINIT, FAIL, "unable to create link")

done:
    H5MM_xfree(ext_link_buf);
    H5MM_xfree(norm_obj_name);

    FUNC_LEAVE_API(ret_value)
}
