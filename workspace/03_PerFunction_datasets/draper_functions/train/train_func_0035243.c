nfs_readdir_make_qstr(struct qstr *string, const char *name, unsigned int len)
{
	string->len = len;
	string->name = kmemdup(name, len, GFP_KERNEL);
	if (string->name == NULL)
		return -ENOMEM;


	kmemleak_not_leak(string->name);
	string->hash = full_name_hash(name, len);
	return 0;
}
