recursive_hash(VALUE range, VALUE dummy, int recur)
{
    st_index_t hash = EXCL(range);
    VALUE v;

    hash = rb_hash_start(hash);
    if (!recur) {
	v = rb_hash(RANGE_BEG(range));
	hash = rb_hash_uint(hash, NUM2LONG(v));
	v = rb_hash(RANGE_END(range));
	hash = rb_hash_uint(hash, NUM2LONG(v));
    }
    hash = rb_hash_uint(hash, EXCL(range) << 24);
    hash = rb_hash_end(hash);

    return LONG2FIX(hash);
}
