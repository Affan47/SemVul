rb_hash_aref(VALUE hash, VALUE key)
{
    st_data_t val;

    if (!RHASH(hash)->ntbl || !st_lookup(RHASH(hash)->ntbl, key, &val)) {
	if (!FL_TEST(hash, HASH_PROC_DEFAULT) &&
	    rb_method_basic_definition_p(CLASS_OF(hash), id_default)) {
	    return RHASH_IFNONE(hash);
	}
	else {
	    return rb_funcall(hash, id_default, 1, key);
	}
    }
    return (VALUE)val;
}
