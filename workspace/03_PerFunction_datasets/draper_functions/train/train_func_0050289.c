trx_sys_file_format_max_check(

	ulint	max_format_id)
{
	ulint	format_id;


	format_id = trx_sys_file_format_max_read();
	if (format_id == ULINT_UNDEFINED) {


		format_id = DICT_TF_FORMAT_MIN;
	}

	ut_print_timestamp(stderr);
	fprintf(stderr,
		" InnoDB: highest supported file format is %s.\n",
		trx_sys_file_format_id_to_name(DICT_TF_FORMAT_MAX));

	if (format_id > DICT_TF_FORMAT_MAX) {

		ut_a(format_id < FILE_FORMAT_NAME_N);

		ut_print_timestamp(stderr);
		fprintf(stderr,
			" InnoDB: %s: the system tablespace is in a file "
			"format that this version doesn't support - %s\n",
			((max_format_id <= DICT_TF_FORMAT_MAX)
				? "Error" : "Warning"),
			trx_sys_file_format_id_to_name(format_id));

		if (max_format_id <= DICT_TF_FORMAT_MAX) {
			return(DB_ERROR);
		}
	}

	format_id = (format_id > max_format_id) ? format_id : max_format_id;


	file_format_max.id = format_id;
	file_format_max.name = trx_sys_file_format_id_to_name(format_id);

	return(DB_SUCCESS);
}
