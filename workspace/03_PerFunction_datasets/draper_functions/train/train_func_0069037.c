hash_equal(VALUE hash1, VALUE hash2, int eql)
{
    struct equal_data data;

    if (hash1 == hash2) return Qtrue;
    if (TYPE(hash2) != T_HASH) {
	if (!rb_respond_to(hash2, rb_intern("to_hash"))) {
	    return Qfalse;
	}
	if (eql)
	    return rb_eql(hash2, hash1);
	else
	    return rb_equal(hash2, hash1);
    }
    if (RHASH_SIZE(hash1) != RHASH_SIZE(hash2))
	return Qfalse;
    if (!RHASH(hash1)->ntbl || !RHASH(hash2)->ntbl)
        return Qtrue;
    if (RHASH(hash1)->ntbl->type != RHASH(hash2)->ntbl->type)
	return Qfalse;
#if 0
    if (!(rb_equal(RHASH_IFNONE(hash1), RHASH_IFNONE(hash2)) &&
	  FL_TEST(hash1, HASH_PROC_DEFAULT) == FL_TEST(hash2, HASH_PROC_DEFAULT)))
	return Qfalse;
#endif

    data.tbl = RHASH(hash2)->ntbl;
    data.eql = eql;
    return rb_exec_recursive_paired(recursive_eql, hash1, hash2, (VALUE)&data);
}
