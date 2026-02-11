H5G__create_named(const H5G_loc_t *loc, const char *name, hid_t lcpl_id,
    hid_t gcpl_id, hid_t gapl_id, hid_t dxpl_id)
{
    H5O_obj_create_t ocrt_info;
    H5G_obj_create_t gcrt_info;
    H5G_t	   *ret_value;

    FUNC_ENTER_PACKAGE


    HDassert(loc);
    HDassert(name && *name);
    HDassert(lcpl_id != H5P_DEFAULT);
    HDassert(gcpl_id != H5P_DEFAULT);
    HDassert(gapl_id != H5P_DEFAULT);
    HDassert(dxpl_id != H5P_DEFAULT);


    gcrt_info.gcpl_id = gcpl_id;
    gcrt_info.cache_type = H5G_NOTHING_CACHED;
    HDmemset(&gcrt_info.cache, 0, sizeof(gcrt_info.cache));


    ocrt_info.obj_type = H5O_TYPE_GROUP;
    ocrt_info.crt_info = &gcrt_info;
    ocrt_info.new_obj = NULL;


    if(H5L_link_object(loc, name, &ocrt_info, lcpl_id, gapl_id, dxpl_id) < 0)
        HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, NULL, "unable to create and link to group")
    HDassert(ocrt_info.new_obj);


    ret_value = (H5G_t *)ocrt_info.new_obj;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
