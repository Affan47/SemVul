clean_up() {

	file_list *next_file;
	file_list *old_file;
	interp_list *next_interp;
	interp_list *old_interp;
	interp_inventory *pointer;
	interp_inventory *deleter;


	next_file = file_header->next_file;
	old_file = file_header;
	free(old_file);

	while (next_file != NULL) {

          old_file = next_file;
          next_file = next_file->next_file;
          free(old_file);
	}


	next_interp = interp_header;
	while (next_interp != NULL) {
		old_interp = next_interp;
		next_interp = next_interp->next_interp;
		free(old_interp);
	}


	pointer = ex_inven_header;
	while (pointer != NULL) {
		deleter = pointer;
		pointer = pointer->next_interp;
		free(deleter);
	}


	pointer = tand_inven_header;
	while (pointer != NULL) {
		deleter = pointer;
		pointer = pointer->next_interp;
		free(deleter);
	}
}
