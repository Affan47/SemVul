H5FD_sec2_write(H5FD_t *_file, H5FD_mem_t UNUSED type, hid_t UNUSED dxpl_id, haddr_t addr,
		size_t size, const void *buf)
{
    H5FD_sec2_t		*file = (H5FD_sec2_t*)_file;
    ssize_t		nbytes;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5FD_sec2_write, FAIL)

    HDassert(file && file->pub.cls);
    HDassert(buf);


    if(!H5F_addr_defined(addr))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "addr undefined, addr = %llu", (unsigned long long)addr)
    if(REGION_OVERFLOW(addr, size))
        HGOTO_ERROR(H5E_ARGS, H5E_OVERFLOW, FAIL, "addr overflow, addr = %llu, size = %llu", (unsigned long long)addr, (unsigned long long)size)
    if((addr + size) > file->eoa)
        HGOTO_ERROR(H5E_ARGS, H5E_OVERFLOW, FAIL, "addr overflow, addr = %llu, size = %llu, eoa = %llu", (unsigned long long)addr, (unsigned long long)size, (unsigned long long)file->eoa)


    if((addr != file->pos || OP_WRITE != file->op) &&
            HDlseek(file->fd, (file_offset_t)addr, SEEK_SET) < 0)
        HSYS_GOTO_ERROR(H5E_IO, H5E_SEEKERROR, FAIL, "unable to seek to proper position")


    while(size > 0) {
        do {
            nbytes = HDwrite(file->fd, buf, size);
        } while(-1 == nbytes && EINTR == errno);
        if(-1 == nbytes) {
            int myerrno = errno;
            time_t mytime = HDtime(NULL);
            file_offset_t myoffset = HDlseek(file->fd, (file_offset_t)0, SEEK_CUR);

            HGOTO_ERROR(H5E_IO, H5E_WRITEERROR, FAIL, "file write failed: time = %s, filename = '%s', file descriptor = %d, errno = %d, error message = '%s', buf = %p, size = %lu, offset = %llu", HDctime(&mytime), file->filename, file->fd, myerrno, HDstrerror(myerrno), buf, (unsigned long)size, (unsigned long long)myoffset);
        }
        HDassert(nbytes > 0);
        HDassert((size_t)nbytes <= size);
        H5_CHECK_OVERFLOW(nbytes, ssize_t, size_t);
        size -= (size_t)nbytes;
        H5_CHECK_OVERFLOW(nbytes, ssize_t, haddr_t);
        addr += (haddr_t)nbytes;
        buf = (const char *)buf + nbytes;
    }


    file->pos = addr;
    file->op = OP_WRITE;
    if(file->pos > file->eof)
        file->eof = file->pos;

done:
    if(ret_value < 0) {

        file->pos = HADDR_UNDEF;
        file->op = OP_UNKNOWN;
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
