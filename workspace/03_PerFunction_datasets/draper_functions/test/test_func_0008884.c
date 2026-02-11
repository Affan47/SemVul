rb_io_readlines(argc, argv, io)
    int argc;
    VALUE *argv;
    VALUE io;
{
    VALUE line, ary;
    VALUE rs;

    if (argc == 0) {
	rs = rb_rs;
    }
    else {
	rb_scan_args(argc, argv, "1", &rs);
	if (!NIL_P(rs)) StringValue(rs);
    }
    ary = rb_ary_new();
    while (!NIL_P(line = rb_io_getline(rs, io))) {
	rb_ary_push(ary, line);
    }
    return ary;
}
