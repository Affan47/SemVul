perm_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct perm_datum *perdatum;
	int rc;
	__le32 buf[2];
	u32 len;

	rc = -ENOMEM;
	perdatum = kzalloc(sizeof(*perdatum), GFP_KERNEL);
	if (!perdatum)
		goto bad;

	rc = next_entry(buf, fp, sizeof buf);
	if (rc)
		goto bad;

	len = le32_to_cpu(buf[0]);
	perdatum->value = le32_to_cpu(buf[1]);

	rc = str_read(&key, GFP_KERNEL, fp, len);
	if (rc)
		goto bad;

	rc = hashtab_insert(h, key, perdatum);
	if (rc)
		goto bad;

	return 0;
bad:
	perm_destroy(key, perdatum, NULL);
	return rc;
}
