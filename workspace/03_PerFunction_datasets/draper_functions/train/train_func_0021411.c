rb_ary_last(int argc, VALUE *argv, VALUE ary)
{
    if (argc == 0) {
	if (RARRAY_LEN(ary) == 0) return Qnil;
	return RARRAY_PTR(ary)[RARRAY_LEN(ary)-1];
    }
    else {
	return ary_take_first_or_last(argc, argv, ary, ARY_TAKE_LAST);
    }
}
