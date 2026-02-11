stab_enum(stab_t st, stab_callback_t cb, void *user_data)
{
	int ret;
	struct addr_key akey;

	ret = btree_select(st->addr, NULL, BTREE_FIRST,
			   &akey, NULL);
	while (!ret) {
		if (cb(user_data, akey.name, akey.addr) < 0)
			return -1;
		ret = btree_select(st->addr, NULL, BTREE_NEXT,
				   &akey, NULL);
	}

	return 0;
}
