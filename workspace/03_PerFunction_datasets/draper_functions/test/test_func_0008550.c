H5FD_core_flush(H5FD_t *_file, hid_t UNUSED dxpl_id, unsigned UNUSED closing)
{
    H5FD_core_t	*file = (H5FD_core_t*)_file;
    herr_t      ret_value=SUCCEED;

    FUNC_ENTER_NOAPI(H5FD_core_flush, FAIL)


    if (file->dirty && file->fd>=0 && file->backing_store) {
        haddr_t size = file->eof;
        unsigned char *ptr = file->mem;

        if (0!=HDlseek(file->fd, (off_t)0, SEEK_SET))
            HGOTO_ERROR(H5E_IO, H5E_SEEKERROR, FAIL, "error seeking in backing store")

        while (size) {
            ssize_t n;

            H5_CHECK_OVERFLOW(size,hsize_t,size_t);
            n = HDwrite(file->fd, ptr, (size_t)size);
            if (n<0 && EINTR==errno)
                continue;
            if (n<0)
                HGOTO_ERROR(H5E_IO, H5E_WRITEERROR, FAIL, "error writing backing store")
            ptr += (size_t)n;
            size -= (size_t)n;
        }
        file->dirty = FALSE;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
