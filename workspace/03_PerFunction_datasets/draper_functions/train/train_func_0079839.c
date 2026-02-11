git_hashsig_create(
	git_hashsig **out,
	const char *buf,
	size_t buflen,
	git_hashsig_option_t opts)
{
	int error;
	hashsig_in_progress prog;
	git_hashsig *sig = hashsig_alloc(opts);
	GITERR_CHECK_ALLOC(sig);

	hashsig_in_progress_init(&prog, sig);

	error = hashsig_add_hashes(sig, (const uint8_t *)buf, buflen, &prog);

	if (!error)
		error = hashsig_finalize_hashes(sig);

	if (!error)
		*out = sig;
	else
		git_hashsig_free(sig);

	return error;
}
