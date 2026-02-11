op_div (struct val *a, struct val *b)
{
	struct val *r;

	if (!to_number (a)) {
		free_value(a);
		free_value(b);
		if( !extra_error_message_supplied )
			ast_log(LOG_WARNING, "non-numeric argument\n");
		return make_number(0);
	} else if (!to_number (b)) {
		free_value(a);
		free_value(b);
		if( !extra_error_message_supplied )
			ast_log(LOG_WARNING, "non-numeric argument\n");
		return make_number(INT_MAX);
	}

	if (b->u.i == 0) {
		ast_log(LOG_WARNING, "division by zero\n");
		free_value(a);
		free_value(b);
		return make_number(INT_MAX);
	}

	r = make_number (a->u.i / b->u.i);
	if (chk_div (a->u.i, b->u.i)) {
		ast_log(LOG_WARNING, "overflow\n");
	}
	free_value (a);
	free_value (b);
	return r;
}
