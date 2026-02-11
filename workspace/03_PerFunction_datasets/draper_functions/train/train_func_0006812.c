argf_read(argc, argv)
    int argc;
    VALUE *argv;
{
    VALUE tmp, str, length;
    long len = 0;

    rb_scan_args(argc, argv, "02", &length, &str);
    if (!NIL_P(length)) {
	len = NUM2LONG(argv[0]);
    }
    if (!NIL_P(str)) {
	StringValue(str);
	rb_str_resize(str,0);
	argv[1] = Qnil;
    }

  retry:
    if (!next_argv()) {
	return str;
    }
    if (TYPE(current_file) != T_FILE) {
	tmp = argf_forward();
    }
    else {
	tmp = io_read(argc, argv, current_file);
    }
    if (NIL_P(str)) str = tmp;
    else if (!NIL_P(tmp)) rb_str_append(str, tmp);
    if (NIL_P(tmp) || NIL_P(length)) {
	if (next_p != -1) {
	    argf_close(current_file);
	    next_p = 1;
	    goto retry;
	}
    }
    else if (argc >= 1) {
	if (RSTRING(str)->len < len) {
	    len -= RSTRING(str)->len;
	    argv[0] = INT2NUM(len);
	    goto retry;
	}
    }
    return str;
}
