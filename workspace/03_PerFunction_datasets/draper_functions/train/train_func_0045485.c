cifs_ci_hash(const struct dentry *dentry, struct qstr *q)
{
	struct nls_table *codepage = CIFS_SB(dentry->d_sb)->local_nls;
	unsigned long hash;
	wchar_t c;
	int i, charlen;

	hash = init_name_hash();
	for (i = 0; i < q->len; i += charlen) {
		charlen = codepage->char2uni(&q->name[i], q->len - i, &c);

		if (unlikely(charlen < 0))
			return charlen;
		hash = partial_name_hash(cifs_toupper(c), hash);
	}
	q->hash = end_name_hash(hash);

	return 0;
}
