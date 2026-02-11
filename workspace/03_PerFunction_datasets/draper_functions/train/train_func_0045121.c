H5FD_stdio_write(H5FD_t *_file, H5FD_mem_t type, hid_t dxpl_id, haddr_t addr,
    size_t size, const void *buf)
{
    H5FD_stdio_t    *file = (H5FD_stdio_t*)_file;
    static const char *func = "H5FD_stdio_write";


    dxpl_id = dxpl_id;
    type = type;


    H5Eclear2(H5E_DEFAULT);


    if (HADDR_UNDEF == addr)
        H5Epush_ret (func, H5E_ERR_CLS, H5E_IO, H5E_OVERFLOW, "file address overflowed", -1)
    if (REGION_OVERFLOW(addr, size))
        H5Epush_ret (func, H5E_ERR_CLS, H5E_IO, H5E_OVERFLOW, "file address overflowed", -1)


    if ((file->op != H5FD_STDIO_OP_WRITE && file->op != H5FD_STDIO_OP_SEEK) ||
                file->pos != addr) {
        if (file_fseek(file->fp, (file_offset_t)addr, SEEK_SET) < 0) {
            file->op = H5FD_STDIO_OP_UNKNOWN;
            file->pos = HADDR_UNDEF;
            H5Epush_ret(func, H5E_ERR_CLS, H5E_IO, H5E_SEEKERROR, "fseek failed", -1)
        }
        file->pos = addr;
    }


    while(size > 0) {

        size_t bytes_in        = 0;
        size_t bytes_wrote     = 0;
        size_t item_size       = 1;

        if(size > H5_STDIO_MAX_IO_BYTES_g)
            bytes_in = H5_STDIO_MAX_IO_BYTES_g;
        else
            bytes_in = size;

        bytes_wrote = fwrite(buf, item_size, bytes_in, file->fp);

        if(bytes_wrote != bytes_in || (0 == bytes_wrote && ferror(file->fp))) {
            file->op = H5FD_STDIO_OP_UNKNOWN;
            file->pos = HADDR_UNDEF;
            H5Epush_ret(func, H5E_ERR_CLS, H5E_IO, H5E_WRITEERROR, "fwrite failed", -1)
        }

        assert(bytes_wrote > 0);
        assert((size_t)bytes_wrote <= size);

        size -= bytes_wrote;
        addr += (haddr_t)bytes_wrote;
        buf = (const char *)buf + bytes_wrote;
    }


    file->op = H5FD_STDIO_OP_WRITE;
    file->pos = addr;


    if (file->pos > file->eof)
        file->eof = file->pos;

    return 0;
}
