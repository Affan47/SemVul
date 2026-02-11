recv_msg_userauth_pk_ok() {

	struct SignKeyList *keyitem = NULL;
	buffer* keybuf = NULL;
	char* algotype = NULL;
	unsigned int algolen;
	int keytype;
	unsigned int remotelen;

	TRACE(("enter recv_msg_userauth_pk_ok"))

	algotype = buf_getstring(ses.payload, &algolen);
	keytype = signkey_type_from_name(algotype, algolen);
	TRACE(("recv_msg_userauth_pk_ok: type %d", keytype))
	m_free(algotype);

	keybuf = buf_new(MAX_PUBKEY_SIZE);

	remotelen = buf_getint(ses.payload);


	for (keyitem = cli_opts.privkeys; keyitem != NULL; keyitem = keyitem->next) {

		if (keyitem->type != keytype) {

			TRACE(("types differed"))
			continue;
		}


		keybuf->pos = keybuf->len = 0;
		buf_put_pub_key(keybuf, keyitem->key, keytype);
		buf_setpos(keybuf, 0);
		buf_incrpos(keybuf, 4);


		if (keybuf->len-4 != remotelen) {
			TRACE(("lengths differed: localh %d remote %d", keybuf->len, remotelen))

			continue;
		}
		if (memcmp(buf_getptr(keybuf, remotelen),
					buf_getptr(ses.payload, remotelen), remotelen) != 0) {

			TRACE(("data differed"))
			continue;
		}


		break;
	}
	buf_free(keybuf);

	if (keyitem != NULL) {
		TRACE(("matching key"))


		send_msg_userauth_pubkey(keyitem->key, keytype, 1);
	} else {
		TRACE(("That was whacky. We got told that a key was valid, but it didn't match our list. Sounds like dodgy code on Dropbear's part"))
	}

	TRACE(("leave recv_msg_userauth_pk_ok"))
}
