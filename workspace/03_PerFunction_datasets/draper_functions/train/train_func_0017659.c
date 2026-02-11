avx_usable(void)
{
	if (!cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM, NULL)) {
		if (cpu_has_avx)
			pr_info("AVX detected but unusable.\n");
		return false;
	}

	return true;
}
