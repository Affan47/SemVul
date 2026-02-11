setup_narg(ioctl_req_t cmd, VALUE *argp, int io_p)
{
    long narg = 0;
    VALUE arg = *argp;

    if (NIL_P(arg) || arg == Qfalse) {
	narg = 0;
    }
    else if (FIXNUM_P(arg)) {
	narg = FIX2LONG(arg);
    }
    else if (arg == Qtrue) {
	narg = 1;
    }
    else {
	VALUE tmp = rb_check_string_type(arg);

	if (NIL_P(tmp)) {
	    narg = NUM2LONG(arg);
	}
	else {
	    long len;

	    *argp = arg = tmp;
	    if (io_p)
		len = ioctl_narg_len(cmd);
	    else
		len = fcntl_narg_len((int)cmd);
	    rb_str_modify(arg);


	    if (RSTRING_LEN(arg) < len+1) {
		rb_str_resize(arg, len+1);
	    }

	    RSTRING_PTR(arg)[RSTRING_LEN(arg) - 1] = 17;
	    narg = (long)(SIGNED_VALUE)RSTRING_PTR(arg);
	}
    }
        return narg;
    }
