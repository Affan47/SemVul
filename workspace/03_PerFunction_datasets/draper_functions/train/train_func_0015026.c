__zswap_pool_create_fallback(void)
{
	if (!crypto_has_comp(zswap_compressor, 0, 0)) {
		if (!strcmp(zswap_compressor, ZSWAP_COMPRESSOR_DEFAULT)) {
			pr_err("default compressor %s not available\n",
			       zswap_compressor);
			return NULL;
		}
		pr_err("compressor %s not available, using default %s\n",
		       zswap_compressor, ZSWAP_COMPRESSOR_DEFAULT);
		param_free_charp(&zswap_compressor);
		zswap_compressor = ZSWAP_COMPRESSOR_DEFAULT;
	}
	if (!zpool_has_pool(zswap_zpool_type)) {
		if (!strcmp(zswap_zpool_type, ZSWAP_ZPOOL_DEFAULT)) {
			pr_err("default zpool %s not available\n",
			       zswap_zpool_type);
			return NULL;
		}
		pr_err("zpool %s not available, using default %s\n",
		       zswap_zpool_type, ZSWAP_ZPOOL_DEFAULT);
		param_free_charp(&zswap_zpool_type);
		zswap_zpool_type = ZSWAP_ZPOOL_DEFAULT;
	}

	return zswap_pool_create(zswap_zpool_type, zswap_compressor);
}
