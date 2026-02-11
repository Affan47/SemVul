convert_dup2_x1(struct parse_context *ctx)
{
	struct expression *value1, *value2, *value3;


	value1 = stack_pop(ctx->bb->mimic_stack);
	value2 = stack_pop(ctx->bb->mimic_stack);

	if (value1->vm_type == J_LONG || value1->vm_type == J_DOUBLE) {
		return __convert_dup_x1(ctx, value1, value2);
	} else {
		value3 = stack_pop(ctx->bb->mimic_stack);
		return __convert_dup2_x1(ctx, value1, value2, value3);
	}
}
