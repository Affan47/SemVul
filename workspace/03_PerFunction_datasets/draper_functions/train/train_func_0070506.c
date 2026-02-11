H5D__create_named(const H5G_loc_t *loc, const char *name, hid_t type_id,
    const H5S_t *space, hid_t lcpl_id, hid_t dcpl_id, hid_t dapl_id,
    hid_t dxpl_id)
{
    H5O_obj_create_t ocrt_info;
    H5D_obj_create_t dcrt_info;
    H5D_t	   *ret_value;

    FUNC_ENTER_PACKAGE


    HDassert(loc);
    HDassert(name && *name);
    HDassert(type_id != H5P_DEFAULT);
    HDassert(space);
    HDassert(lcpl_id != H5P_DEFAULT);
    HDassert(dcpl_id != H5P_DEFAULT);
    HDassert(dapl_id != H5P_DEFAULT);
    HDassert(dxpl_id != H5P_DEFAULT);


    dcrt_info.type_id = type_id;
    dcrt_info.space = space;
    dcrt_info.dcpl_id = dcpl_id;
    dcrt_info.dapl_id = dapl_id;


    ocrt_info.obj_type = H5O_TYPE_DATASET;
    ocrt_info.crt_info = &dcrt_info;
    ocrt_info.new_obj = NULL;


    if(H5L_link_object(loc, name, &ocrt_info, lcpl_id, dapl_id, dxpl_id) < 0)
        HGOTO_ERROR(H5E_DATASET, H5E_CANTINIT, NULL, "unable to create and link to dataset")
    HDassert(ocrt_info.new_obj);


    ret_value = (H5D_t *)ocrt_info.new_obj;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
