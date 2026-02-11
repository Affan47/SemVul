rb_hash_default_proc(VALUE hash)
{
    if (FL_TEST(hash, HASH_PROC_DEFAULT)) {
	return RHASH_IFNONE(hash);
    }
    return Qnil;
}
