H5FD_sec2_read(H5FD_t *_file, H5FD_mem_t UNUSED type, hid_t UNUSED dxpl_id,
    haddr_t addr, size_t size, void *buf)
{
    H5FD_sec2_t		*file = (H5FD_sec2_t *)_file;
    ssize_t		nbytes;
    herr_t              ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5FD_sec2_read)

    HDassert(file && file->pub.cls);
    HDassert(buf);


    if(!H5F_addr_defined(addr))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "addr undefined, addr = %llu", (unsigned long long)addr)
    if(REGION_OVERFLOW(addr, size))
        HGOTO_ERROR(H5E_ARGS, H5E_OVERFLOW, FAIL, "addr overflow, addr = %llu", (unsigned long long)addr)
    if((addr + size) > file->eoa)
        HGOTO_ERROR(H5E_ARGS, H5E_OVERFLOW, FAIL, "addr overflow, addr = %llu", (unsigned long long)addr)


    if(addr != file->pos || OP_READ != file->op) {
        if(HDlseek(file->fd, (HDoff_t)addr, SEEK_SET) < 0)
            HSYS_GOTO_ERROR(H5E_IO, H5E_SEEKERROR, FAIL, "unable to seek to proper position")
    }


    while(size > 0) {
        do {
            nbytes = HDread(file->fd, buf, size);
        } while(-1 == nbytes && EINTR == errno);
        if(-1 == nbytes) {
            int myerrno = errno;
            time_t mytime = HDtime(NULL);
            HDoff_t myoffset = HDlseek(file->fd, (HDoff_t)0, SEEK_CUR);

            HGOTO_ERROR(H5E_IO, H5E_READERROR, FAIL, "file read failed: time = %s, filename = '%s', file descriptor = %d, errno = %d, error message = '%s', buf = %p, size = %lu, offset = %llu", HDctime(&mytime), file->filename, file->fd, myerrno, HDstrerror(myerrno), buf, (unsigned long)size, (unsigned long long)myoffset);
        }
        if(0 == nbytes) {

            HDmemset(buf, 0, size);
            break;
        }
        HDassert(nbytes >= 0);
        HDassert((size_t)nbytes <= size);
        H5_CHECK_OVERFLOW(nbytes, ssize_t, size_t);
        size -= (size_t)nbytes;
        H5_CHECK_OVERFLOW(nbytes, ssize_t, haddr_t);
        addr += (haddr_t)nbytes;
        buf = (char *)buf + nbytes;
    }


    file->pos = addr;
    file->op = OP_READ;

done:
    if(ret_value < 0) {

        file->pos = HADDR_UNDEF;
        file->op = OP_UNKNOWN;
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
