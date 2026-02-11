srv_shutdown_print_master_pending(

	ib_time_t*	last_print_time,

	ulint		n_tables_to_drop,

	ulint		n_bytes_merged,

	ulint		n_pages_flushed)
{
	ib_time_t	current_time;
	double		time_elapsed;

	current_time = ut_time();
	time_elapsed = ut_difftime(current_time, *last_print_time);

	if (time_elapsed > 60) {
		*last_print_time = ut_time();

		if (n_tables_to_drop) {
			ut_print_timestamp(stderr);
			fprintf(stderr, "  InnoDB: Waiting for "
				"%lu table(s) to be dropped\n",
				(ulong) n_tables_to_drop);
		}


		if (!srv_fast_shutdown && n_bytes_merged) {
			ut_print_timestamp(stderr);
			fprintf(stderr, "  InnoDB: Waiting for change "
				"buffer merge to complete\n"
				"  InnoDB: number of bytes of change buffer "
				"just merged:  %lu\n",
				n_bytes_merged);
		}

		if (n_pages_flushed) {
			ut_print_timestamp(stderr);
			fprintf(stderr, "  InnoDB: Waiting for "
				"%lu pages to be flushed\n",
				(ulong) n_pages_flushed);
		}
        }
}
