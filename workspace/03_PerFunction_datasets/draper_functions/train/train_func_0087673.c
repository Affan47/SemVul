poly1305_simd_mod_init(void)
{
	if (!cpu_has_xmm2)
		return -ENODEV;

#ifdef CONFIG_AS_AVX2
	poly1305_use_avx2 = cpu_has_avx && cpu_has_avx2 &&
			    cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM, NULL);
	alg.descsize = sizeof(struct poly1305_simd_desc_ctx);
	if (poly1305_use_avx2)
		alg.descsize += 10 * sizeof(u32);
#endif
	return crypto_register_shash(&alg);
}
