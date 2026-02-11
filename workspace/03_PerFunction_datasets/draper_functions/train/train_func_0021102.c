close_faxd(fz_context *ctx, void *state_)
{
	fz_faxd *fax = (fz_faxd *)state_;
	int i;


	i = (32 - fax->bidx) / 8;
	while (i--)
		fz_unread_byte(fax->chain);

	fz_close(fax->chain);
	fz_free(ctx, fax->ref);
	fz_free(ctx, fax->dst);
	fz_free(ctx, fax);
}
