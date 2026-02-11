nm_utils_wep_key_valid (const char *key, NMWepKeyType wep_type)
{
	int keylen, i;

	if (!key)
		return FALSE;

	keylen = strlen (key);
	if (   wep_type == NM_WEP_KEY_TYPE_KEY
	    || wep_type == NM_WEP_KEY_TYPE_UNKNOWN) {
		if (keylen == 10 || keylen == 26) {

			for (i = 0; i < keylen; i++) {
				if (!g_ascii_isxdigit (key[i]))
					return FALSE;
			}
		} else if (keylen == 5 || keylen == 13) {

			for (i = 0; i < keylen; i++) {
				if (!g_ascii_isprint (key[i]))
					return FALSE;
			}
		} else
			return FALSE;

	} else if (wep_type == NM_WEP_KEY_TYPE_PASSPHRASE) {
		if (!keylen || keylen > 64)
			return FALSE;
	}

	return TRUE;
}
