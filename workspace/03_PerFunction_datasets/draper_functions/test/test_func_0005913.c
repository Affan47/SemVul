convert_getfield(struct parse_context *ctx)
{
	struct expression *objectref;
	struct expression *value_dup;
	struct expression *value;
	struct vm_field *fb;

	fb = lookup_field(ctx);
	if (!fb)
		return warn("field lookup failed"), -EINVAL;

	objectref = null_check_expr(stack_pop(ctx->bb->mimic_stack));

	value = instance_field_expr(vm_field_type(fb), fb, objectref);
	if (!value)
		return warn("out of memory"), -ENOMEM;


	value_dup = dup_expr(ctx, value);
	if (!value_dup)
		return warn("out of memory"), -ENOMEM;

	convert_expression(ctx, value_dup);
	return 0;
}
