add_token(u16 number, char *name)
{
	token_t *curr;

	curr = malloc(sizeof(token_t));
	if (!curr) {
		printf("Out of memory while adding token.\n");
		exit(-ENOMEM);
	}

	curr->name = name;
	curr->fcode=number;

	link_token( curr);

	if (check_tok_seq) {

		if ((number == last_defined_token + 1)
		    || (last_defined_token == 0)) {
			last_defined_token = number;
		} else {
			if (number <= last_defined_token) {
				printremark("Warning:  New token # might overlap "
						"previously assigned token #(s).");
			} else {
				printremark("Warning:  New token # out of sequence with "
				     		"previously assigned token #(s).");

				last_defined_token = number;
			}
		}
	}

}
