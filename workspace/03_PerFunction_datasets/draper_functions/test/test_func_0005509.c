rb_file_join(VALUE ary, VALUE sep)
{
    long len, i;
    VALUE result, tmp;
    const char *name, *tail;

    if (RARRAY_LEN(ary) == 0) return rb_str_new(0, 0);

    len = 1;
    for (i=0; i<RARRAY_LEN(ary); i++) {
	tmp = RARRAY_PTR(ary)[i];
	if (RB_TYPE_P(tmp, T_STRING)) {
	    len += RSTRING_LEN(tmp);
	}
	else {
	    len += 10;
	}
    }
    if (!NIL_P(sep)) {
	StringValue(sep);
	len += RSTRING_LEN(sep) * RARRAY_LEN(ary) - 1;
    }
    result = rb_str_buf_new(len);
    OBJ_INFECT(result, ary);
    for (i=0; i<RARRAY_LEN(ary); i++) {
	tmp = RARRAY_PTR(ary)[i];
	switch (TYPE(tmp)) {
	  case T_STRING:
	    break;
	  case T_ARRAY:
	    if (ary == tmp) {
		rb_raise(rb_eArgError, "recursive array");
	    }
	    else {
		VALUE args[2];

		args[0] = tmp;
		args[1] = sep;
		tmp = rb_exec_recursive(file_inspect_join, ary, (VALUE)args);
	    }
	    break;
	  default:
	    FilePathStringValue(tmp);
	}
	name = StringValueCStr(result);
	len = RSTRING_LEN(result);
	if (i == 0) {
	    rb_enc_copy(result, tmp);
	}
	else if (!NIL_P(sep)) {
	    tail = chompdirsep(name, name + len, rb_enc_get(result));
	    if (RSTRING_PTR(tmp) && isdirsep(RSTRING_PTR(tmp)[0])) {
		rb_str_set_len(result, tail - name);
	    }
	    else if (!*tail) {
		rb_str_buf_append(result, sep);
	    }
	}
	rb_str_buf_append(result, tmp);
    }

    return result;
}
