rb_hash_size(VALUE hash)
{
    if (!RHASH(hash)->ntbl)
        return INT2FIX(0);
    return INT2FIX(RHASH(hash)->ntbl->num_entries);
}
