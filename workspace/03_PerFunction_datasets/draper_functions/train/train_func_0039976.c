ast_aoc_add_unit_entry(struct ast_aoc_decoded *decoded,
		const unsigned int amount_is_present,
		const unsigned int amount,
		const unsigned int type_is_present,
		const unsigned int type)
{
	if ((decoded->msg_type == AST_AOC_REQUEST) ||
		(decoded->unit_count >= ARRAY_LEN(decoded->unit_list))) {
		return -1;
	}

	if (!amount_is_present && !type_is_present) {
		return -1;
	}

	decoded->unit_list[decoded->unit_count].valid_amount = amount_is_present;
	if (amount_is_present) {
		decoded->unit_list[decoded->unit_count].amount = amount;
	} else {
		decoded->unit_list[decoded->unit_count].amount = 0;
	}

	decoded->unit_list[decoded->unit_count].valid_type = type_is_present;
	if (type_is_present) {
		decoded->unit_list[decoded->unit_count].type = type;
	} else {
		decoded->unit_list[decoded->unit_count].type = 0;
	}
	decoded->unit_count++;

	return 0;
}
