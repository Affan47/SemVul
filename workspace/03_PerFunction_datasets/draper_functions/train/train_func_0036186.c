H5D__ioinfo_xfer_mode(H5D_io_info_t *io_info, H5P_genplist_t *dx_plist,
    H5FD_mpio_xfer_t xfer_mode)
{
    herr_t  ret_value = SUCCEED;

    FUNC_ENTER_STATIC


    io_info->dxpl_cache->xfer_mode = xfer_mode;
    if(H5P_set(dx_plist, H5D_XFER_IO_XFER_MODE_NAME, &io_info->dxpl_cache->xfer_mode) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTSET, FAIL, "can't set transfer mode")


    if(xfer_mode == H5FD_MPIO_INDEPENDENT) {

        io_info->io_ops.single_read = io_info->orig.io_ops.single_read;
        io_info->io_ops.single_write = io_info->orig.io_ops.single_write;
    }
    else {
        HDassert(xfer_mode == H5FD_MPIO_COLLECTIVE);


        io_info->io_ops.single_read = H5D__mpio_select_read;
        io_info->io_ops.single_write = H5D__mpio_select_write;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
