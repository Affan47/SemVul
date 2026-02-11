rb_hash_clear(VALUE hash)
{
    rb_hash_modify_check(hash);
    if (!RHASH(hash)->ntbl)
        return hash;
    if (RHASH(hash)->ntbl->num_entries > 0) {
	if (RHASH(hash)->iter_lev > 0)
	    rb_hash_foreach(hash, clear_i, 0);
	else
	    st_clear(RHASH(hash)->ntbl);
    }

    return hash;
}
