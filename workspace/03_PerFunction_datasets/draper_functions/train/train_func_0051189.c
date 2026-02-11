ast_aoc_get_currency_multiplier_decimal(struct ast_aoc_decoded *decoded)
{
	switch (decoded->multiplier) {
	case AST_AOC_MULT_ONETHOUSANDTH:
		return "0.001";
	case AST_AOC_MULT_ONEHUNDREDTH:
		return "0.01";
	case AST_AOC_MULT_ONETENTH:
		return "0.1";
	case AST_AOC_MULT_ONE:
		return "1.0";
	case AST_AOC_MULT_TEN:
		return "10.0";
	case AST_AOC_MULT_HUNDRED:
		return "100.0";
	case AST_AOC_MULT_THOUSAND:
		return "1000.0";
	default:
		return "1.0";
	}
}
