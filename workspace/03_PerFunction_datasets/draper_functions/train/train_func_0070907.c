io_getpartial(int argc, VALUE *argv, VALUE io)
{
    OpenFile *fptr;
    VALUE length, str;
    long n, len;

    rb_scan_args(argc, argv, "11", &length, &str);

    if ((len = NUM2LONG(length)) < 0) {
        rb_raise(rb_eArgError, "negative length %ld given", len);
    }

    if (NIL_P(str)) {
        str = rb_str_new(0, len);
    }
    else {
        StringValue(str);
        rb_str_modify(str);
        rb_str_resize(str, len);
    }
    OBJ_TAINT(str);

    GetOpenFile(io, fptr);
    rb_io_check_readable(fptr);

    if (len == 0)
        return str;

    READ_CHECK(fptr->f);
    if (RSTRING(str)->len != len) {
      modified:
        rb_raise(rb_eRuntimeError, "buffer string modified");
    }
    n = read_buffered_data(RSTRING(str)->ptr, len, fptr->f);
    if (n <= 0) {
      again:
        if (RSTRING(str)->len != len) goto modified;
        TRAP_BEG;
        n = read(fileno(fptr->f), RSTRING(str)->ptr, len);
        TRAP_END;
        if (n < 0) {
            if (rb_io_wait_readable(fileno(fptr->f)))
                goto again;
            rb_sys_fail(fptr->path);
        }
    }
    rb_str_resize(str, n);

    if (n == 0)
        return Qnil;
    else
        return str;
}
