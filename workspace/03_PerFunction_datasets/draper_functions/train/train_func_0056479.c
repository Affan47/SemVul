clean_trustedkey()
{
	int i = 0;

	for (i= 0; i < MAX_TRUSTED_KEY; i++) {
		if (tk_list.key[i] != NULL) {
			dst_key_free(&tk_list.key[i]);
			tk_list.key[i] = NULL;
		} else
			break;
	}
	tk_list.nb_tk = 0;
	return;
}
