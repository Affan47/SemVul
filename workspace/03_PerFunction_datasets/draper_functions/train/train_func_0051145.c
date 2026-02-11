__hamc_dup(orig_dbc, new_dbc)
	DBC *orig_dbc, *new_dbc;
{
	HASH_CURSOR *orig, *new;

	orig = (HASH_CURSOR *)orig_dbc->internal;
	new = (HASH_CURSOR *)new_dbc->internal;

	new->bucket = orig->bucket;
	new->lbucket = orig->lbucket;
	new->dup_off = orig->dup_off;
	new->dup_len = orig->dup_len;
	new->dup_tlen = orig->dup_tlen;

	if (F_ISSET(orig, H_DELETED))
		F_SET(new, H_DELETED);
	if (F_ISSET(orig, H_ISDUP))
		F_SET(new, H_ISDUP);

	return (0);
}
