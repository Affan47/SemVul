parse_on_statement (result, cfile, lose)
	struct executable_statement **result;
	struct parse *cfile;
	int *lose;
{
	enum dhcp_token token;
	const char *val;

	if (!executable_statement_allocate (result, MDL))
		log_fatal ("no memory for new statement.");
	(*result) -> op = on_statement;

	do {
		token = next_token (&val, (unsigned *)0, cfile);
		switch (token) {
		      case EXPIRY:
			(*result) -> data.on.evtypes |= ON_EXPIRY;
			break;

		      case COMMIT:
			(*result) -> data.on.evtypes |= ON_COMMIT;
			break;

		      case RELEASE:
			(*result) -> data.on.evtypes |= ON_RELEASE;
			break;

		      case TRANSMISSION:
			(*result) -> data.on.evtypes |= ON_TRANSMISSION;
			break;

		      default:
			parse_warn (cfile, "expecting a lease event type");
			skip_to_semi (cfile);
			*lose = 1;
			executable_statement_dereference (result, MDL);
			return 0;
		}
		token = next_token (&val, (unsigned *)0, cfile);
	} while (token == OR);


	if (token == SEMI)
		return 1;

	if (token != LBRACE) {
		parse_warn (cfile, "left brace expected.");
		skip_to_semi (cfile);
		*lose = 1;
		executable_statement_dereference (result, MDL);
		return 0;
	}
	if (!parse_executable_statements (&(*result) -> data.on.statements,
					  cfile, lose, context_any)) {
		if (*lose) {

			do {
				token = next_token (&val,
						    (unsigned *)0, cfile);
			} while (token != END_OF_FILE && token != RBRACE);
			executable_statement_dereference (result, MDL);
			return 0;
		}
	}
	token = next_token (&val, (unsigned *)0, cfile);
	if (token != RBRACE) {
		parse_warn (cfile, "right brace expected.");
		skip_to_semi (cfile);
		*lose = 1;
		executable_statement_dereference (result, MDL);
		return 0;
	}
	return 1;
}
