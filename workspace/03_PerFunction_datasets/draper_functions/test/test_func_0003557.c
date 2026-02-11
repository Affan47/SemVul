verify_sha1_digest(const struct verify *ctx)
{
	g_return_val_if_fail(verify_status(ctx) == VERIFY_DONE, NULL);
	return &verify_sha1.digest;
}
