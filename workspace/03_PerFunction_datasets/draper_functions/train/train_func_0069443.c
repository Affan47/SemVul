process_indicators(tokens fields) {

	interp_list *current;
	interp_list *previous;


	current = interp_header->next_interp;
	previous = interp_header;
	while (current != NULL) {


		switch(current->indicator) {
			case '^':
				current = do_split(current);
				break;
			case '-':
				current = do_terminate(current,previous);
				break;
			case 'x':
				current = do_exchange(current);
				break;
			case 'v':
				current = do_join(current);
				break;
			case '+':
				current = do_add(current);
				break;
		}
		previous = current;
		current = current->next_interp;
	}
}
