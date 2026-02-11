ary_join_1(VALUE obj, VALUE ary, VALUE sep, long i, VALUE result, int *first)
{
    VALUE val, tmp;

    for (; i<RARRAY_LEN(ary); i++) {
	if (i > 0 && !NIL_P(sep))
	    rb_str_buf_append(result, sep);

	val = RARRAY_PTR(ary)[i];
	switch (TYPE(val)) {
	  case T_STRING:
	  str_join:
	    rb_str_buf_append(result, val);
	    *first = FALSE;
	    break;
	  case T_ARRAY:
	    obj = val;
	  ary_join:
	    if (val == ary) {
		rb_raise(rb_eArgError, "recursive array join");
	    }
	    else {
		VALUE args[4];

		args[0] = val;
		args[1] = sep;
		args[2] = result;
		args[3] = (VALUE)first;
		rb_exec_recursive(recursive_join, obj, (VALUE)args);
	    }
	    break;
	  default:
	    tmp = rb_check_string_type(val);
	    if (!NIL_P(tmp)) {
		val = tmp;
		goto str_join;
	    }
	    tmp = rb_check_convert_type(val, T_ARRAY, "Array", "to_ary");
	    if (!NIL_P(tmp)) {
		obj = val;
		val = tmp;
		goto ary_join;
	    }
	    val = rb_obj_as_string(val);
	    if (*first) {
		rb_enc_copy(result, val);
		*first = FALSE;
	    }
	    goto str_join;
	}
    }
}
