cmp_all(void *binary, int count)
{
#if MD5_std_mt
	int t, n = (count + (MD5_N - 1)) / MD5_N;
#endif
	for_each_t(n) {
#if MD5_X2
		if (*(MD5_word *)binary == MD5_out[0][0] ||
		    *(MD5_word *)binary == MD5_out[1][0])
			return 1;
#else
		if (*(MD5_word *)binary == MD5_out[0][0])
			return 1;
#endif
	}
	return 0;
}
