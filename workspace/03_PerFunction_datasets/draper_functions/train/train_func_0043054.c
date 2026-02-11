c_coll_idlist_set (VALUE self, VALUE ids)
{
	int i;
	int *ary = NULL;
	VALUE *rb_ary;
	int rb_ary_len;

	Check_Type (ids, T_ARRAY);
	COLL_METHOD_HANDLER_HEADER

	rb_ary = RARRAY_PTR (ids);
	rb_ary_len = RARRAY_LEN (ids);

	ary = malloc (sizeof (int *) * (rb_ary_len + 1));

	for (i = 0; i < rb_ary_len; i++)
		ary[i] = NUM2INT (rb_ary[i]);

	ary[i] = 0;

	xmmsc_coll_set_idlist (coll->real, ary);

	return self;
}
