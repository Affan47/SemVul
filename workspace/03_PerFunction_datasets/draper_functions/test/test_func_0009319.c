aim_newsnac(aim_session_t *sess, aim_snac_t *newsnac)
{
	aim_snac_t *snac;
	int index;

	if (!newsnac)
		return 0;

	if (!(snac = malloc(sizeof(aim_snac_t))))
		return 0;
	memcpy(snac, newsnac, sizeof(aim_snac_t));
	snac->issuetime = time(NULL);

	index = snac->id % FAIM_SNAC_HASH_SIZE;

	snac->next = (aim_snac_t *)sess->snac_hash[index];
	sess->snac_hash[index] = (void *)snac;

	return snac->id;
}
