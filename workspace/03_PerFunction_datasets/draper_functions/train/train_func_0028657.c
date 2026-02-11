rb_io_sysseek(int argc, VALUE *argv, VALUE io)
{
    VALUE offset, ptrname;
    int whence = SEEK_SET;
    rb_io_t *fptr;
    off_t pos;

    if (rb_scan_args(argc, argv, "11", &offset, &ptrname) == 2) {
	whence = NUM2INT(ptrname);
    }
    pos = NUM2OFFT(offset);
    GetOpenFile(io, fptr);
    if ((fptr->mode & FMODE_READABLE) &&
        (READ_DATA_BUFFERED(fptr) || READ_CHAR_PENDING(fptr))) {
	rb_raise(rb_eIOError, "sysseek for buffered IO");
    }
    if ((fptr->mode & FMODE_WRITABLE) && fptr->wbuf.len) {
	rb_warn("sysseek for buffered IO");
    }
    errno = 0;
    pos = lseek(fptr->fd, pos, whence);
    if (pos == -1 && errno) rb_sys_fail_path(fptr->pathv);

    return OFFT2NUM(pos);
}
