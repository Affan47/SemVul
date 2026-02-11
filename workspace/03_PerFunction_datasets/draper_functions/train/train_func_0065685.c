is_numeric_expression (expr)
	struct expression *expr;
{
	return (expr -> op == expr_extract_int8 ||
		expr -> op == expr_extract_int16 ||
		expr -> op == expr_extract_int32 ||
		expr -> op == expr_const_int ||
		expr -> op == expr_lease_time ||
		expr -> op == expr_dns_transaction ||
		expr -> op == expr_add ||
		expr -> op == expr_subtract ||
		expr -> op == expr_multiply ||
		expr -> op == expr_divide ||
		expr -> op == expr_remainder ||
		expr -> op == expr_binary_and ||
		expr -> op == expr_binary_or ||
		expr -> op == expr_binary_xor ||
		expr -> op == expr_client_state);
}
