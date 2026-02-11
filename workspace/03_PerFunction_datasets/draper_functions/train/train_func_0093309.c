filter_parse(struct filter_parse_state *ps)
{
	int in_string = 0;
	int op, top_op;
	char ch;

	while ((ch = infix_next(ps))) {
		if (ch == '"') {
			in_string ^= 1;
			continue;
		}

		if (in_string)
			goto parse_operand;

		if (isspace(ch))
			continue;

		if (is_op_char(ps, ch)) {
			op = infix_get_op(ps, ch);
			if (op == OP_NONE) {
				parse_error(ps, FILT_ERR_INVALID_OP, 0);
				return -EINVAL;
			}

			if (strlen(curr_operand(ps))) {
				postfix_append_operand(ps, curr_operand(ps));
				clear_operand_string(ps);
			}

			while (!filter_opstack_empty(ps)) {
				top_op = filter_opstack_top(ps);
				if (!is_precedence_lower(ps, top_op, op)) {
					top_op = filter_opstack_pop(ps);
					postfix_append_op(ps, top_op);
					continue;
				}
				break;
			}

			filter_opstack_push(ps, op);
			continue;
		}

		if (ch == '(') {
			filter_opstack_push(ps, OP_OPEN_PAREN);
			continue;
		}

		if (ch == ')') {
			if (strlen(curr_operand(ps))) {
				postfix_append_operand(ps, curr_operand(ps));
				clear_operand_string(ps);
			}

			top_op = filter_opstack_pop(ps);
			while (top_op != OP_NONE) {
				if (top_op == OP_OPEN_PAREN)
					break;
				postfix_append_op(ps, top_op);
				top_op = filter_opstack_pop(ps);
			}
			if (top_op == OP_NONE) {
				parse_error(ps, FILT_ERR_UNBALANCED_PAREN, 0);
				return -EINVAL;
			}
			continue;
		}
parse_operand:
		if (append_operand_char(ps, ch)) {
			parse_error(ps, FILT_ERR_OPERAND_TOO_LONG, 0);
			return -EINVAL;
		}
	}

	if (strlen(curr_operand(ps)))
		postfix_append_operand(ps, curr_operand(ps));

	while (!filter_opstack_empty(ps)) {
		top_op = filter_opstack_pop(ps);
		if (top_op == OP_NONE)
			break;
		if (top_op == OP_OPEN_PAREN) {
			parse_error(ps, FILT_ERR_UNBALANCED_PAREN, 0);
			return -EINVAL;
		}
		postfix_append_op(ps, top_op);
	}

	return 0;
}
