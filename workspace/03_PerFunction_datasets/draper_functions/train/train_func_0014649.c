cm_submit_x_fault_text(struct cm_submit_x_context *ctx)
{
	return ctx->fault_occurred ? ctx->fault_text : NULL;
}
