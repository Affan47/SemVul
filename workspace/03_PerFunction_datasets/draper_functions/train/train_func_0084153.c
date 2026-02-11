H5FD_family_flush(H5FD_t *_file, hid_t dxpl_id, unsigned closing)
{
    H5FD_family_t	*file = (H5FD_family_t*)_file;
    unsigned		u, nerrors = 0;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5FD_family_flush, FAIL)

    for(u = 0; u < file->nmembs; u++)
        if(file->memb[u] && H5FD_flush(file->memb[u], dxpl_id, closing) < 0)
            nerrors++;

    if(nerrors)
        HGOTO_ERROR(H5E_IO, H5E_BADVALUE, FAIL, "unable to flush member files")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
