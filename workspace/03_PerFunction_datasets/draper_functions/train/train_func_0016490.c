row_drop_database_for_mysql(

	const char*	name,
	trx_t*		trx)
{
	dict_table_t* table;
	char*	table_name;
	int	err	= DB_SUCCESS;
	ulint	namelen	= strlen(name);

	ut_a(name != NULL);
	ut_a(name[namelen - 1] == '/');

	trx->op_info = "dropping database";

	trx_start_if_not_started(trx);
loop:
	row_mysql_lock_data_dictionary(trx);

	while ((table_name = dict_get_first_table_name_in_db(name))) {
		ut_a(memcmp(table_name, name, namelen) == 0);

		table = dict_table_get_low(table_name, DICT_ERR_IGNORE_NONE);

		ut_a(table);


		if (table->n_mysql_handles_opened > 0) {
			row_mysql_unlock_data_dictionary(trx);

			ut_print_timestamp(stderr);
			fputs("  InnoDB: Warning: MySQL is trying to"
			      " drop database ", stderr);
			ut_print_name(stderr, trx, TRUE, name);
			fputs("\n"
			      "InnoDB: though there are still"
			      " open handles to table ", stderr);
			ut_print_name(stderr, trx, TRUE, table_name);
			fputs(".\n", stderr);

			os_thread_sleep(1000000);

			mem_free(table_name);

			goto loop;
		}

		err = row_drop_table_for_mysql(table_name, trx, TRUE);
		trx_commit_for_mysql(trx);

		if (err != DB_SUCCESS) {
			fputs("InnoDB: DROP DATABASE ", stderr);
			ut_print_name(stderr, trx, TRUE, name);
			fprintf(stderr, " failed with error %lu for table ",
				(ulint) err);
			ut_print_name(stderr, trx, TRUE, table_name);
			putc('\n', stderr);
			mem_free(table_name);
			break;
		}

		mem_free(table_name);
	}

	if (err == DB_SUCCESS) {


		err = (int) drop_all_foreign_keys_in_db(name, trx);

		if (err != DB_SUCCESS) {
			fputs("InnoDB: DROP DATABASE ", stderr);
			ut_print_name(stderr, trx, TRUE, name);
			fprintf(stderr, " failed with error %d while "
				"dropping all foreign keys", err);
		}
	}

	trx_commit_for_mysql(trx);

	row_mysql_unlock_data_dictionary(trx);

	trx->op_info = "";

	return(err);
}
