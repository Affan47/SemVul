sens_read(struct policydb *p, struct hashtab *h, void *fp)
{
	char *key = NULL;
	struct level_datum *levdatum;
	int rc;
	__le32 buf[2];
	u32 len;

	rc = -ENOMEM;
	levdatum = kzalloc(sizeof(*levdatum), GFP_ATOMIC);
	if (!levdatum)
		goto bad;

	rc = next_entry(buf, fp, sizeof buf);
	if (rc)
		goto bad;

	len = le32_to_cpu(buf[0]);
	levdatum->isalias = le32_to_cpu(buf[1]);

	rc = str_read(&key, GFP_ATOMIC, fp, len);
	if (rc)
		goto bad;

	rc = -ENOMEM;
	levdatum->level = kmalloc(sizeof(struct mls_level), GFP_ATOMIC);
	if (!levdatum->level)
		goto bad;

	rc = mls_read_level(levdatum->level, fp);
	if (rc)
		goto bad;

	rc = hashtab_insert(h, key, levdatum);
	if (rc)
		goto bad;
	return 0;
bad:
	sens_destroy(key, levdatum, NULL);
	return rc;
}
