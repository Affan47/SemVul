make_host_lookup (expr, name)
	struct expression **expr;
	const char *name;
{
	if (!expression_allocate (expr, MDL)) {
		log_error ("No memory for host lookup tree node.");
		return 0;
	}
	(*expr) -> op = expr_host_lookup;
	if (!enter_dns_host (&((*expr) -> data.host_lookup), name)) {
		expression_dereference (expr, MDL);
		return 0;
	}
	return 1;
}
