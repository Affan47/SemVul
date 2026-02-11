primary(enum token n)
{
#if TEST_DEBUG
	number_t res = res;
#else
	number_t res;
#endif
	const struct operator_t *args0_op;

	nest_msg(">primary(%s)\n", TOKSTR[n]);
	if (n == EOI) {
		syntax(NULL, "argument expected");
	}
	if (n == LPAREN) {
		res = oexpr(check_operator(*++args));
		if (check_operator(*++args) != RPAREN)
			syntax(NULL, "closing paren expected");
		unnest_msg("<primary:%lld\n", res);
		return res;
	}


	args0_op = last_operator;

	if (check_operator(args[1]) != EOI) {
		if (args[2]) {


			if (last_operator->op_type == BINOP)
				unnest_msg_and_return(binop(), "<primary: binop:%lld\n");
		}
	}

	if (args0_op->op_type == UNOP) {

		if (args[1] == NULL)

			goto check_emptiness;
		args++;
		if (n == STREZ)
			unnest_msg_and_return(args[0][0] == '\0', "<primary:%lld\n");
		if (n == STRNZ)
			unnest_msg_and_return(args[0][0] != '\0', "<primary:%lld\n");
		if (n == FILTT)
			unnest_msg_and_return(isatty(getn(*args)), "<primary: isatty(%s)%lld\n", *args);
		unnest_msg_and_return(filstat(*args, n), "<primary: filstat(%s):%lld\n", *args);
	}


	if (last_operator->op_type == BINOP) {

		unnest_msg_and_return(binop(), "<primary:%lld\n");
	}
 check_emptiness:
	unnest_msg_and_return(args[0][0] != '\0', "<primary:%lld\n");
}
