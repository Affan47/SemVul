H5Z_prepare_prelude_callback_dcpl(hid_t dcpl_id, hid_t type_id, H5Z_prelude_type_t prelude_type)
{
    hid_t space_id = -1;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5Z_prepare_prelude_callback_dcpl)

    HDassert(H5I_GENPROP_LST == H5I_get_type(dcpl_id));
    HDassert(H5I_DATATYPE == H5I_get_type(type_id));


    if(dcpl_id != H5P_DATASET_CREATE_DEFAULT) {
        H5P_genplist_t 	*dc_plist;
        H5O_layout_t    dcpl_layout;


        if(NULL == (dc_plist = (H5P_genplist_t *)H5I_object(dcpl_id)))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "can't get dataset creation property list")


        if(H5P_get(dc_plist, H5D_CRT_LAYOUT_NAME, &dcpl_layout) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't retrieve layout")


        if(H5D_CHUNKED == dcpl_layout.type) {
            H5O_pline_t     dcpl_pline;


            if(H5P_get(dc_plist, H5O_CRT_PIPELINE_NAME, &dcpl_pline) < 0)
                HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't retrieve pipeline filter")


            if(dcpl_pline.nused > 0) {
                hsize_t chunk_dims[H5O_LAYOUT_NDIMS];
                H5S_t *space;
                size_t u;


                for(u = 0; u < dcpl_layout.u.chunk.ndims; u++)
                    chunk_dims[u] = dcpl_layout.u.chunk.dim[u];
                if(NULL == (space = H5S_create_simple(dcpl_layout.u.chunk.ndims, chunk_dims, NULL)))
                    HGOTO_ERROR(H5E_DATASPACE, H5E_CANTCREATE, FAIL, "can't create simple dataspace")


                if((space_id = H5I_register(H5I_DATASPACE, space, FALSE)) < 0) {
                    (void)H5S_close(space);
                    HGOTO_ERROR(H5E_ATOM, H5E_CANTREGISTER, FAIL, "unable to register dataspace ID")
                }


                if(H5Z_prelude_callback(&dcpl_pline, dcpl_id, type_id, space_id, prelude_type) < 0)
                    HGOTO_ERROR(H5E_PLINE, H5E_CANAPPLY, FAIL, "unable to apply filter")
            }
        }
    }

done:
    if(space_id > 0 && H5I_dec_ref(space_id, FALSE) < 0)
        HDONE_ERROR(H5E_PLINE, H5E_CANTRELEASE, FAIL, "unable to close dataspace")

    FUNC_LEAVE_NOAPI(ret_value)
}
