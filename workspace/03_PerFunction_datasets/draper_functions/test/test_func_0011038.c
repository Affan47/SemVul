set_ue_keys(snmp_ue_assoc_t* n ) {
	guint key_size = n->user.authModel->key_size;

	n->user.authKey.data = (guint8 *)g_malloc(key_size);
	n->user.authKey.len = key_size;
	n->user.authModel->pass2key(n->user.authPassword.data,
				    n->user.authPassword.len,
				    n->engine.data,
				    n->engine.len,
				    n->user.authKey.data);

	if (n->priv_proto == PRIV_AES128 || n->priv_proto == PRIV_AES192 || n->priv_proto == PRIV_AES256) {
		guint need_key_len =
			(n->priv_proto == PRIV_AES128) ? 16 :
			(n->priv_proto == PRIV_AES192) ? 24 :
			(n->priv_proto == PRIV_AES256) ? 32 :
			0;

		guint key_len = key_size;

		while (key_len < need_key_len)
			key_len += key_size;

		n->user.privKey.data = (guint8 *)g_malloc(key_len);
		n->user.privKey.len  = need_key_len;

		n->user.authModel->pass2key(n->user.privPassword.data,
					    n->user.privPassword.len,
					    n->engine.data,
					    n->engine.len,
					    n->user.privKey.data);

		key_len = key_size;


		while (key_len < need_key_len) {
			n->user.authModel->pass2key(
				n->user.privKey.data,
				key_len,
				n->engine.data,
				n->engine.len,
				n->user.privKey.data + key_len);

			key_len += key_size;
		}

	} else {
		n->user.privKey.data = (guint8 *)g_malloc(key_size);
		n->user.privKey.len = key_size;
		n->user.authModel->pass2key(n->user.privPassword.data,
					    n->user.privPassword.len,
					    n->engine.data,
					    n->engine.len,
					    n->user.privKey.data);
	}
}
