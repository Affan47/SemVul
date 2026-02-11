fqdncache_get(const char *name)
{
    hash_link *e;
    static fqdncache_entry *f;
    f = NULL;
    if (fqdn_table) {
	if ((e = hash_lookup(fqdn_table, name)) != NULL)
	    f = (fqdncache_entry *) e;
    }
    return f;
}
