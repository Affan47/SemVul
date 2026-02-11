io_write(io, str)
    VALUE io, str;
{
    OpenFile *fptr;
    long n;

    rb_secure(4);
    if (TYPE(str) != T_STRING)
	str = rb_obj_as_string(str);

    if (TYPE(io) != T_FILE) {

	return rb_funcall(io, id_write, 1, str);
    }
    if (RSTRING(str)->len == 0) return INT2FIX(0);

    GetOpenFile(io, fptr);
    rb_io_check_writable(fptr);

    n = io_fwrite(str, fptr);
    if (n == -1L) rb_sys_fail(fptr->path);
    if (!(fptr->mode & FMODE_SYNC)) {
	fptr->mode |= FMODE_WBUF;
    }

    return LONG2FIX(n);
}
