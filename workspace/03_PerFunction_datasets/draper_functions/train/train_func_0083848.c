bsock_close_read(VALUE sock)
{
    rb_io_t *fptr;

    if (rb_safe_level() >= 4 && !OBJ_TAINTED(sock)) {
	rb_raise(rb_eSecurityError, "Insecure: can't close socket");
    }
    GetOpenFile(sock, fptr);
    shutdown(fptr->fd, 0);
    if (!(fptr->mode & FMODE_WRITABLE)) {
	return rb_io_close(sock);
    }
    fptr->mode &= ~FMODE_READABLE;

    return Qnil;
}
