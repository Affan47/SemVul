check_hmac_md5(const dst_private_t *priv, isc_boolean_t old) {
	int i, j;

	if (priv->nelements != HMACMD5_NTAGS) {


		if (old && priv->nelements == OLD_HMACMD5_NTAGS &&
		    priv->elements[0].tag == TAG_HMACMD5_KEY)
			return (0);
		return (-1);
	}


	for (i = 0; i < HMACMD5_NTAGS; i++) {
		for (j = 0; j < priv->nelements; j++)
			if (priv->elements[j].tag == TAG(DST_ALG_HMACMD5, i))
				break;
		if (j == priv->nelements)
			return (-1);
	}
	return (0);
}
