range_min(VALUE range)
{
    if (rb_block_given_p()) {
	return rb_call_super(0, 0);
    }
    else {
	VALUE b = RANGE_BEG(range);
	VALUE e = RANGE_END(range);
	int c = rb_cmpint(rb_funcall(b, id_cmp, 1, e), b, e);

	if (c > 0 || (c == 0 && EXCL(range)))
	    return Qnil;
	return b;
    }
}
