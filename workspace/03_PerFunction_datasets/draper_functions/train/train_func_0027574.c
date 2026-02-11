istgt_find_cf_nitem(CF_SECTION *sp, const char *key, int idx)
{
	CF_ITEM *ip;
	int i;

	if (key == NULL || key[0] == '\0')
		return NULL;

	i = 0;
	for (ip = sp->item; ip != NULL; ip = ip->next) {
		if (ip->key != NULL && ip->key[0] == key[0]
			&& strcasecmp(ip->key, key) == 0) {
			if (i == idx) {
				return ip;
			}
			i++;
		}
	}

	return NULL;
}
