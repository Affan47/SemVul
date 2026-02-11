cmd_window_close(const char *data)
{
        GSList *tmp, *destroys;
	char *first, *last;
        int first_num, last_num;
	void *free_arg;

	if (!cmd_get_params(data, &free_arg, 2, &first, &last))
		return;

	if ((*first != '\0' && !is_numeric(first, '\0')) ||
	    ((*last != '\0') && !is_numeric(last, '\0'))) {
		cmd_params_free(free_arg);
                return;
	}

	first_num = *first == '\0' ? active_win->refnum : atoi(first);
	last_num = *last == '\0' ? first_num : atoi(last);


        destroys = NULL;
	for (tmp = windows; tmp != NULL; tmp = tmp->next) {
		WINDOW_REC *rec = tmp->data;

		if (rec->refnum >= first_num && rec->refnum <= last_num)
			destroys = g_slist_append(destroys, rec);
	}


	while (destroys != NULL) {
		WINDOW_REC *rec = destroys->data;

		if (windows->next != NULL) {
			if (!rec->immortal)
				window_destroy(rec);
			else {
				printformat_window(rec, MSGLEVEL_CLIENTERROR,
						   TXT_WINDOW_IMMORTAL_ERROR);
			}
		}

                destroys = g_slist_remove(destroys, rec);
	}

	cmd_params_free(free_arg);
}
