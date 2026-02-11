recursive_hash(VALUE s, VALUE dummy, int recur)
{
    long i, len;
    st_index_t h;
    VALUE n, *ptr;

    h = rb_hash_start(rb_hash(rb_obj_class(s)));
    if (!recur) {
	ptr = RSTRUCT_PTR(s);
	len = RSTRUCT_LEN(s);
	for (i = 0; i < len; i++) {
	    n = rb_hash(ptr[i]);
	    h = rb_hash_uint(h, NUM2LONG(n));
	}
    }
    h = rb_hash_end(h);
    return INT2FIX(h);
}
