verify_tth_leave_count(const struct verify *ctx)
{
	g_return_val_if_fail(verify_status(ctx) == VERIFY_DONE, 0);
	return tt_leave_count(verify_tth.context);
}
