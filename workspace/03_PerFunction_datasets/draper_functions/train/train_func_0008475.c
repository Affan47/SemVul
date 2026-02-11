jfs_ci_hash(const struct dentry *dir, struct qstr *this)
{
	unsigned long hash;
	int i;

	hash = init_name_hash();
	for (i=0; i < this->len; i++)
		hash = partial_name_hash(tolower(this->name[i]), hash);
	this->hash = end_name_hash(hash);

	return 0;
}
