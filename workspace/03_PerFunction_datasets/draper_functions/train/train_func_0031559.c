efivarfs_d_hash(const struct dentry *dentry, struct qstr *qstr)
{
	unsigned long hash = init_name_hash();
	const unsigned char *s = qstr->name;
	unsigned int len = qstr->len;

	if (!efivarfs_valid_name(s, len))
		return -EINVAL;

	while (len-- > EFI_VARIABLE_GUID_LEN)
		hash = partial_name_hash(*s++, hash);


	while (len--)
		hash = partial_name_hash(tolower(*s++), hash);

	qstr->hash = end_name_hash(hash);
	return 0;
}
