H5FD_stdio_read(H5FD_t *_file, H5FD_mem_t type, hid_t dxpl_id, haddr_t addr, size_t size,
    void *buf)
{
    H5FD_stdio_t    *file = (H5FD_stdio_t*)_file;
    static const char *func = "H5FD_stdio_read";


    type = type;
    dxpl_id = dxpl_id;


    H5Eclear2(H5E_DEFAULT);


    if (HADDR_UNDEF==addr)
        H5Epush_ret (func, H5E_ERR_CLS, H5E_IO, H5E_OVERFLOW, "file address overflowed", -1)
    if (REGION_OVERFLOW(addr, size))
        H5Epush_ret (func, H5E_ERR_CLS, H5E_IO, H5E_OVERFLOW, "file address overflowed", -1)
    if((addr + size) > file->eoa)
        H5Epush_ret(func, H5E_ERR_CLS, H5E_IO, H5E_OVERFLOW, "file address overflowed", -1)


    if (0 == size)
        return 0;
    if ((haddr_t)addr >= file->eof) {
        memset(buf, 0, size);
        return 0;
    }


    if (!(file->op == H5FD_STDIO_OP_READ || file->op == H5FD_STDIO_OP_SEEK) ||
            file->pos != addr) {
        if (file_fseek(file->fp, (file_offset_t)addr, SEEK_SET) < 0) {
            file->op = H5FD_STDIO_OP_UNKNOWN;
            file->pos = HADDR_UNDEF;
            H5Epush_ret(func, H5E_ERR_CLS, H5E_IO, H5E_SEEKERROR, "fseek failed", -1)
        }
        file->pos = addr;
    }


    if (addr + size > file->eof) {
        size_t nbytes = (size_t) (addr + size - file->eof);
        memset((unsigned char *)buf + size - nbytes, 0, nbytes);
        size -= nbytes;
    }


    while(size > 0) {

        size_t bytes_in        = 0;
        size_t bytes_read      = 0;
        size_t item_size       = 1;

        if(size > H5_STDIO_MAX_IO_BYTES_g)
            bytes_in = H5_STDIO_MAX_IO_BYTES_g;
        else
            bytes_in = size;

        bytes_read = fread(buf, item_size, bytes_in, file->fp);

        if(0 == bytes_read && ferror(file->fp)) {
            file->op = H5FD_STDIO_OP_UNKNOWN;
            file->pos = HADDR_UNDEF;
            H5Epush_ret(func, H5E_ERR_CLS, H5E_IO, H5E_READERROR, "fread failed", -1)
        }

        if(0 == bytes_read && feof(file->fp)) {

            memset((unsigned char *)buf, 0, size);
            break;
        }

        size -= bytes_read;
        addr += (haddr_t)bytes_read;
        buf = (char *)buf + bytes_read;
    }


    file->op = H5FD_STDIO_OP_READ;
    file->pos = addr;

    return 0;
}
