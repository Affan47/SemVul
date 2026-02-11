H5Pget_fapl_direct(hid_t fapl_id, size_t *boundary, size_t *block_size,
    size_t *cbuf_size)
{
    H5FD_direct_fapl_t  *fa;
    H5P_genplist_t *plist;
    herr_t      ret_value=SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE4("e", "ixxx", fapl_id, boundary, block_size, cbuf_size);

    if(NULL == (plist = H5P_object_verify(fapl_id,H5P_FILE_ACCESS)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a file access list")
    if (H5FD_DIRECT!=H5P_get_driver(plist))
        HGOTO_ERROR(H5E_PLIST, H5E_BADVALUE, FAIL, "incorrect VFL driver")
    if (NULL==(fa=H5P_get_driver_info(plist)))
        HGOTO_ERROR(H5E_PLIST, H5E_BADVALUE, FAIL, "bad VFL driver info")
    if (boundary)
        *boundary = fa->mboundary;
    if (block_size)
  *block_size = fa->fbsize;
    if (cbuf_size)
  *cbuf_size = fa->cbsize;

done:
    FUNC_LEAVE_API(ret_value)
}
