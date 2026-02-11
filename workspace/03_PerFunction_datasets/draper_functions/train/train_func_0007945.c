hash_foreach_ensure(VALUE hash)
{
    RHASH(hash)->iter_lev--;

    if (RHASH(hash)->iter_lev == 0) {
	if (FL_TEST(hash, HASH_DELETED)) {
	    st_cleanup_safe(RHASH(hash)->ntbl, Qundef);
	    FL_UNSET(hash, HASH_DELETED);
	}
    }
    return 0;
}
