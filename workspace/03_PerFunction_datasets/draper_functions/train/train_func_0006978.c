parse_option_data (expr, cfile, lookups, option)
struct expression **expr;
struct parse *cfile;
int lookups;
struct option *option;
{
	const char *val;
	const char *fmt = NULL;
	struct expression *tmp;
	enum dhcp_token token;

	do {


		int uniform = 0;

	      and_again:


		if ((fmt != NULL) && (fmt != option->format) && (*fmt == 'a'))
			fmt -= 1;
		else if ((fmt == NULL) || (*fmt == 'A'))
			fmt = option->format;


		if ((fmt[0] != 'Z') && (tolower((unsigned char)fmt[1]) == 'a'))
			uniform = 1;

		do {
			if ((*fmt == 'A') || (*fmt == 'a'))
				break;
			if (*fmt == 'o') {

				fmt++;
				continue;
			}

			if (fmt[1] == 'o') {


				token = peek_token(&val, (unsigned *)0,
						   cfile);
				if (token == SEMI) {
					fmt++;
					continue;
				}
			}

			tmp = *expr;
			*expr = NULL;

			if (!parse_option_token(expr, cfile, &fmt, tmp,
						uniform, lookups)) {
				if (fmt [1] != 'o') {
					if (tmp)
						expression_dereference (&tmp,
									MDL);
					return 0;
				}
				*expr = tmp;
				tmp = NULL;
			}
			if (tmp)
				expression_dereference (&tmp, MDL);

			fmt++;
		} while (*fmt != '\0');

		if ((*fmt == 'A') || (*fmt == 'a')) {
			token = peek_token (&val, (unsigned *)0, cfile);

			if (token == COMMA) {
				token = next_token (&val,
						    (unsigned *)0, cfile);
				continue;
			}


			if ((*fmt == 'A') || (fmt[1] == '\0'))
				break;

			if (*fmt == 'a') {
				fmt++;
				goto and_again;
			}
		}
	} while ((*fmt == 'A') || (*fmt == 'a'));

        return 1;
}
