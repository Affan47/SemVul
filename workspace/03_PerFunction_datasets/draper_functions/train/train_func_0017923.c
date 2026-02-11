rb_io_close_write(VALUE io)
{
    rb_io_t *fptr;
    VALUE write_io;

    if (rb_safe_level() >= 4 && !OBJ_UNTRUSTED(io)) {
	rb_raise(rb_eSecurityError, "Insecure: can't close");
    }
    write_io = GetWriteIO(io);
    GetOpenFile(write_io, fptr);
    if (is_socket(fptr->fd, fptr->pathv)) {
#ifndef SHUT_WR
# define SHUT_WR 1
#endif
        if (shutdown(fptr->fd, SHUT_WR) < 0)
            rb_sys_fail_path(fptr->pathv);
        fptr->mode &= ~FMODE_WRITABLE;
        if (!(fptr->mode & FMODE_READABLE))
	    return rb_io_close(write_io);
        return Qnil;
    }

    if (fptr->mode & FMODE_READABLE) {
	rb_raise(rb_eIOError, "closing non-duplex IO for writing");
    }

    if (io != write_io) {
	GetOpenFile(io, fptr);
	fptr->tied_io_for_writing = 0;
	fptr->mode &= ~FMODE_DUPLEX;
    }
    rb_io_close(write_io);
    return Qnil;
}
