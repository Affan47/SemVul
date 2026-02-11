H5Tconvert(hid_t src_id, hid_t dst_id, size_t nelmts, void *buf,
	    void *background, hid_t dxpl_id)
{
    H5T_path_t	*tpath;
    H5T_t	*src, *dst;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE6("e", "iiz*x*xi", src_id, dst_id, nelmts, buf, background, dxpl_id);


    if(NULL == (src = (H5T_t *)H5I_object_verify(src_id, H5I_DATATYPE)) ||
            NULL == (dst = (H5T_t *)H5I_object_verify(dst_id, H5I_DATATYPE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a data type")
    if(H5P_DEFAULT == dxpl_id)
        dxpl_id = H5P_DATASET_XFER_DEFAULT;
    else
        if(TRUE != H5P_isa_class(dxpl_id, H5P_DATASET_XFER))
            HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not dataset transfer property list")


    if(NULL == (tpath = H5T_path_find(src, dst, NULL, NULL, dxpl_id, FALSE)))
	HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "unable to convert between src and dst data types")

    if(H5T_convert(tpath, src_id, dst_id, nelmts, (size_t)0, (size_t)0, buf, background, dxpl_id) < 0)
        HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "data type conversion failed")

done:
    FUNC_LEAVE_API(ret_value)
}
