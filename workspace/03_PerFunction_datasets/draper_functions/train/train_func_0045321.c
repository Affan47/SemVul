dict_print_info_on_foreign_key_in_create_format(

	FILE*		file,
	trx_t*		trx,
	dict_foreign_t*	foreign,
	ibool		add_newline)
{
	const char*	stripped_id;
	ulint	i;

	if (strchr(foreign->id, '/')) {

		stripped_id = foreign->id + 1
			+ dict_get_db_name_len(foreign->id);
	} else {
		stripped_id = foreign->id;
	}

	putc(',', file);

	if (add_newline) {


		fputs("\n ", file);
	}

	fputs(" CONSTRAINT ", file);
	ut_print_name(file, trx, FALSE, stripped_id);
	fputs(" FOREIGN KEY (", file);

	for (i = 0;;) {
		ut_print_name(file, trx, FALSE, foreign->foreign_col_names[i]);
		if (++i < foreign->n_fields) {
			fputs(", ", file);
		} else {
			break;
		}
	}

	fputs(") REFERENCES ", file);

	if (dict_tables_have_same_db(foreign->foreign_table_name_lookup,
				     foreign->referenced_table_name_lookup)) {

		ut_print_name(file, trx, TRUE,
			      dict_remove_db_name(
				      foreign->referenced_table_name));
	} else {
		ut_print_name(file, trx, TRUE,
			      foreign->referenced_table_name);
	}

	putc(' ', file);
	putc('(', file);

	for (i = 0;;) {
		ut_print_name(file, trx, FALSE,
			      foreign->referenced_col_names[i]);
		if (++i < foreign->n_fields) {
			fputs(", ", file);
		} else {
			break;
		}
	}

	putc(')', file);

	if (foreign->type & DICT_FOREIGN_ON_DELETE_CASCADE) {
		fputs(" ON DELETE CASCADE", file);
	}

	if (foreign->type & DICT_FOREIGN_ON_DELETE_SET_NULL) {
		fputs(" ON DELETE SET NULL", file);
	}

	if (foreign->type & DICT_FOREIGN_ON_DELETE_NO_ACTION) {
		fputs(" ON DELETE NO ACTION", file);
	}

	if (foreign->type & DICT_FOREIGN_ON_UPDATE_CASCADE) {
		fputs(" ON UPDATE CASCADE", file);
	}

	if (foreign->type & DICT_FOREIGN_ON_UPDATE_SET_NULL) {
		fputs(" ON UPDATE SET NULL", file);
	}

	if (foreign->type & DICT_FOREIGN_ON_UPDATE_NO_ACTION) {
		fputs(" ON UPDATE NO ACTION", file);
	}
}
