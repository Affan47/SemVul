check_gost(const dst_private_t *priv) {
	if (priv->nelements != GOST_NTAGS)
		return (-1);
	if (priv->elements[0].tag != TAG(DST_ALG_ECCGOST, 0))
		return (-1);
	return (0);
}
