instance_field_expr(enum vm_type vm_type,
				       struct vm_field *instance_field,
				       struct expression *objectref_expression)
{
	struct expression *expr;

	if (vm_type_is_float(vm_type))
		expr = alloc_expression(EXPR_FLOAT_INSTANCE_FIELD, vm_type);
	else
		expr = alloc_expression(EXPR_INSTANCE_FIELD, vm_type);

	if (expr) {
		expr->objectref_expression = &objectref_expression->node;
		expr->instance_field = instance_field;
	}
	return expr;
}
