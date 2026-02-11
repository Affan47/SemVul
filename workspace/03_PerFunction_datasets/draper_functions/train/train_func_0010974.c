rb_ary_zip(int argc, VALUE *argv, VALUE ary)
{
    int i, j;
    long len;
    VALUE result = Qnil;

    len = RARRAY_LEN(ary);
    for (i=0; i<argc; i++) {
	argv[i] = take_items(argv[i], len);
    }
    if (!rb_block_given_p()) {
	result = rb_ary_new2(len);
    }

    for (i=0; i<RARRAY_LEN(ary); i++) {
	VALUE tmp = rb_ary_new2(argc+1);

	rb_ary_push(tmp, rb_ary_elt(ary, i));
	for (j=0; j<argc; j++) {
	    rb_ary_push(tmp, rb_ary_elt(argv[j], i));
	}
	if (NIL_P(result)) {
	    rb_yield(tmp);
	}
	else {
	    rb_ary_push(result, tmp);
	}
    }
    return result;
}
