process_log_fd(void)
{
	llist *entries;
	int ret;
	int do_output = 1;


	do {
		ret = get_record(&entries);
		if ((ret != 0)||(entries->cnt == 0)) {
			break;
		}


		if (match(entries)) {


			if (checkpt_filename)
				do_output = chkpt_output_decision(&entries->e);

			if (do_output == 1) {
				found = 1;
				output_record(entries);


				if (checkpt_filename) {
					if (set_ChkPtLastEvent(&entries->e)) {
						list_clear(entries);
						free(entries);
						fclose(log_fd);
						return 4;
					}
				}
			}
			if (just_one) {
				list_clear(entries);
				free(entries);
				break;
			}
			if (line_buffered)
				fflush(stdout);
		}
		list_clear(entries);
		free(entries);
	} while (ret == 0);
	fclose(log_fd);

	return 0;
}
