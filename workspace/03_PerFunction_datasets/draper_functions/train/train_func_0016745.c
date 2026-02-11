rb_ary_count(int argc, VALUE *argv, VALUE ary)
{
    long i, n = 0;

    if (argc == 0) {
	VALUE v;

	if (!rb_block_given_p())
	    return LONG2NUM(RARRAY_LEN(ary));

	for (i = 0; i < RARRAY_LEN(ary); i++) {
	    v = RARRAY_PTR(ary)[i];
	    if (RTEST(rb_yield(v))) n++;
	}
    }
    else {
	VALUE obj;

	rb_scan_args(argc, argv, "1", &obj);
	if (rb_block_given_p()) {
	    rb_warn("given block not used");
	}
	for (i = 0; i < RARRAY_LEN(ary); i++) {
	    if (rb_equal(RARRAY_PTR(ary)[i], obj)) n++;
	}
    }

    return LONG2NUM(n);
}
