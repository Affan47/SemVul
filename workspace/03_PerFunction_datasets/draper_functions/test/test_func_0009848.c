mgmt_load_link_keys(int index, GSList *keys, gboolean debug_keys)
{
	char *buf;
	struct mgmt_hdr *hdr;
	struct mgmt_cp_load_link_keys *cp;
	struct mgmt_link_key_info *key;
	size_t key_count, cp_size;
	GSList *l;
	int err;

	key_count = g_slist_length(keys);

	DBG("index %d keys %zu debug_keys %d", index, key_count, debug_keys);

	cp_size = sizeof(*cp) + (key_count * sizeof(*key));

	buf = g_try_malloc0(sizeof(*hdr) + cp_size);
	if (buf == NULL)
		return -ENOMEM;

	hdr = (void *) buf;
	hdr->opcode = htobs(MGMT_OP_LOAD_LINK_KEYS);
	hdr->len = htobs(cp_size);
	hdr->index = htobs(index);

	cp = (void *) (buf + sizeof(*hdr));
	cp->debug_keys = debug_keys;
	cp->key_count = htobs(key_count);

	for (l = keys, key = cp->keys; l != NULL; l = g_slist_next(l), key++) {
		struct link_key_info *info = l->data;

		bacpy(&key->addr.bdaddr, &info->bdaddr);
		key->addr.type = BDADDR_BREDR;
		key->type = info->type;
		memcpy(key->val, info->key, 16);
		key->pin_len = info->pin_len;
	}

	if (write(mgmt_sock, buf, sizeof(*hdr) + cp_size) < 0)
		err = -errno;
	else
		err = 0;

	g_free(buf);

	return err;
}
