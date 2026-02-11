rand_xlat(void *instance, REQUEST *request, char *fmt,
			char *out, size_t outlen,
			RADIUS_ESCAPE_STRING func)
{
	int64_t		result;
	rlm_expr_t	*inst = instance;
	char		buffer[256];

	inst = inst;


	if (!radius_xlat(buffer, sizeof(buffer), fmt, request, func)) {
		radlog(L_ERR, "rlm_expr: xlat failed.");
		return 0;
	}

	result = atoi(buffer);


	if (result <= 0) return 0;
	if (result >= (1 << 30)) result = (1 << 30);

	result *= fr_rand();
	result >>= 32;

	snprintf(out, outlen, "%ld", (long int) result);
	return strlen(out);
}
