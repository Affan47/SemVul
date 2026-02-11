rb_ary_join(VALUE ary, VALUE sep)
{
    long len = 1, i;
    int taint = FALSE;
    int untrust = FALSE;
    VALUE val, tmp, result;

    if (RARRAY_LEN(ary) == 0) return rb_usascii_str_new(0, 0);
    if (OBJ_TAINTED(ary) || OBJ_TAINTED(sep)) taint = TRUE;
    if (OBJ_UNTRUSTED(ary) || OBJ_UNTRUSTED(sep)) untrust = TRUE;

    if (!NIL_P(sep)) {
	StringValue(sep);
	len += RSTRING_LEN(sep) * (RARRAY_LEN(ary) - 1);
    }
    for (i=0; i<RARRAY_LEN(ary); i++) {
	val = RARRAY_PTR(ary)[i];
	tmp = rb_check_string_type(val);

	if (NIL_P(tmp) || tmp != val) {
	    int first;
	    result = rb_str_buf_new(len + (RARRAY_LEN(ary)-i)*10);
	    rb_enc_associate(result, rb_usascii_encoding());
	    if (taint) OBJ_TAINT(result);
	    if (untrust) OBJ_UNTRUST(result);
	    ary_join_0(ary, sep, i, result);
	    first = i == 0;
	    ary_join_1(ary, ary, sep, i, result, &first);
	    return result;
	}

	len += RSTRING_LEN(tmp);
    }

    result = rb_str_buf_new(len);
    if (taint) OBJ_TAINT(result);
    if (untrust) OBJ_UNTRUST(result);
    ary_join_0(ary, sep, RARRAY_LEN(ary), result);

    return result;
}
