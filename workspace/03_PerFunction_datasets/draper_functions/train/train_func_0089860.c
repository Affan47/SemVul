H5P_get_fill_value(H5P_genplist_t *plist, const H5T_t *type, void *value,
    hid_t dxpl_id)
{
    H5O_fill_t          fill;
    H5T_path_t		*tpath;
    void		*buf = NULL;
    void		*bkg = NULL;
    hid_t		src_id = -1;
    hid_t		dst_id = -1;
    herr_t              ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5P_get_fill_value, FAIL)


    if(H5P_get(plist, H5D_CRT_FILL_VALUE_NAME, &fill) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get fill value")
    if(fill.size == -1)
	HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "fill value is undefined")


    if(fill.size == 0) {
	HDmemset(value, 0, H5T_get_size(type));
   	HGOTO_DONE(SUCCEED);
    }


    if(NULL == (tpath = H5T_path_find(fill.type, type, NULL, NULL, dxpl_id, FALSE)))
        HGOTO_ERROR(H5E_PLIST, H5E_CANTINIT, FAIL, "unable to convert between src and dst datatypes")
    if((src_id = H5I_register(H5I_DATATYPE, H5T_copy(fill.type, H5T_COPY_TRANSIENT), FALSE)) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTINIT, FAIL, "unable to copy/register datatype")


    if(H5T_get_size(type) >= H5T_get_size(fill.type)) {
        buf = value;
        if(H5T_path_bkg(tpath) && NULL == (bkg = H5MM_malloc(H5T_get_size(type))))
            HGOTO_ERROR(H5E_PLIST, H5E_CANTALLOC, FAIL, "memory allocation failed for type conversion")
    }
    else {
        if(NULL == (buf = H5MM_malloc(H5T_get_size(fill.type))))
            HGOTO_ERROR(H5E_PLIST, H5E_CANTALLOC, FAIL, "memory allocation failed for type conversion")
        if(H5T_path_bkg(tpath))
            bkg = value;
    }
    HDmemcpy(buf, fill.buf, H5T_get_size(fill.type));


    if((dst_id = H5I_register(H5I_DATATYPE, H5T_copy(type, H5T_COPY_TRANSIENT), FALSE)) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTINIT, FAIL, "unable to copy/register datatype")
    if(H5T_convert(tpath, src_id, dst_id, (size_t)1, (size_t)0, (size_t)0, buf, bkg, dxpl_id) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTINIT, FAIL, "datatype conversion failed")
    if(buf != value)
        HDmemcpy(value, buf, H5T_get_size(type));

done:
    if(buf != value)
        H5MM_xfree(buf);
    if(bkg != value)
        H5MM_xfree(bkg);
    if(src_id >= 0 && H5I_dec_ref(src_id) < 0)
        HDONE_ERROR(H5E_PLIST, H5E_CANTDEC, FAIL, "can't decrement ref count of temp ID")
    if(dst_id >= 0 && H5I_dec_ref(dst_id) < 0)
        HDONE_ERROR(H5E_PLIST, H5E_CANTDEC, FAIL, "can't decrement ref count of temp ID")

    FUNC_LEAVE_NOAPI(ret_value)
}
