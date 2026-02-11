parse_additive_expression()
{

    while (TRUE) {
	if (equals(c_token, ".")) {
	    c_token++;
	    accept_multiplicative_expression();
	    (void) add_action(CONCATENATE);


	} else if (string_result_only && parse_recursion_level == 1) {
	    break;
	} else if (equals(c_token, "+")) {
	    c_token++;
	    accept_multiplicative_expression();
	    (void) add_action(PLUS);
	} else if (equals(c_token, "-")) {
	    c_token++;
	    accept_multiplicative_expression();
	    (void) add_action(MINUS);
	} else
	    break;
    }
}
