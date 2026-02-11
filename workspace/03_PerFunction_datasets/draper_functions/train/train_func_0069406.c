process_local(tokens fields) {

	int i;


	if (new_path) {
		print_syntax_error(ERROR1);
		new_path = FALSE;
	}


	if (verbose) {
		local_comments += 1;
	}


	if (!first_interpretation_yet) {
		print_syntax_error(ERROR9);
		current_no_of_spines = fields.number;
	}


	if (fields.number != current_no_of_spines) {
		print_syntax_error(ERROR10);
	}


	for (i = 0; i < fields.number; i += 1) {
		if (strncmp(fields.token[i],"!",1) != 0) {
			print_syntax_error(ERROR11);
		} else if (strncmp(fields.token[i],"!!",2) == 0) {
			print_syntax_error(WARNING1);
		}
	}
}
