dh_create(const struct guid *muid)
{
	dqhit_t *dh;
	const struct guid *key;

	WALLOC0(dh);
	key = atom_guid_get(muid);

	htable_insert(by_muid, key, dh);

	return dh;
}
