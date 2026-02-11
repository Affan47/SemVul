rb_io_write_nonblock(VALUE io, VALUE str)
{
    rb_io_t *fptr;
    long n;

    rb_secure(4);
    if (TYPE(str) != T_STRING)
	str = rb_obj_as_string(str);

    io = GetWriteIO(io);
    GetOpenFile(io, fptr);
    rb_io_check_writable(fptr);

    if (io_fflush(fptr) < 0)
        rb_sys_fail(0);

    rb_io_set_nonblock(fptr);
    n = write(fptr->fd, RSTRING_PTR(str), RSTRING_LEN(str));

    if (n == -1) {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
            rb_mod_sys_fail(rb_mWaitWritable, "write would block");
        rb_sys_fail_path(fptr->pathv);
    }

    return LONG2FIX(n);
}
