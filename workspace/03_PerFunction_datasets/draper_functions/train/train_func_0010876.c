convert_load(struct parse_context *ctx, unsigned int index, enum vm_type type)
{
	struct expression *expr;

	expr = local_expr(type, index);
	if (!expr)
		return warn("out of memory"), -ENOMEM;

	convert_expression(ctx, dup_expr(ctx, expr));
	return 0;
}
