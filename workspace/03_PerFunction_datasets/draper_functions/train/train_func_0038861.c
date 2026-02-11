dicod_acl_lookup(const char *name)
{
    struct dicod_acl samp;
    if (!acl_table)
	return NULL;
    samp.name = (char*) name;
    return hash_lookup(acl_table, &samp);
}
