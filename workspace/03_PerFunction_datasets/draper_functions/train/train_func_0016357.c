moab2slurm_task_list(char *moab_tasklist, int *task_cnt)
{
	char *slurm_tasklist = NULL, *host = NULL, *tmp1 = NULL,
		*tmp2 = NULL, *tok = NULL, *tok_p = NULL;
	int i, reps;
	hostlist_t hl;
	static uint32_t cr_test = 0, cr_enabled = 0;

	if (cr_test == 0) {
		select_g_get_info_from_plugin(SELECT_CR_PLUGIN, NULL,
						&cr_enabled);
		cr_test = 1;
	}

	*task_cnt = 0;


	tmp1 = strchr(moab_tasklist, (int) '*');
	if (tmp1 == NULL)
		tmp1 = strchr(moab_tasklist, (int) '[');

	if (tmp1 == NULL) {
		slurm_tasklist = xstrdup(moab_tasklist);
		if (moab_tasklist[0])
			*task_cnt = 1;
		for (i=0; slurm_tasklist[i]!='\0'; i++) {
			if (slurm_tasklist[i] == ':') {
				slurm_tasklist[i] = ',';
				(*task_cnt)++;
			} else if (slurm_tasklist[i] == ',')
				(*task_cnt)++;
		}
		return slurm_tasklist;
	}


	slurm_tasklist = xstrdup("");
	tmp1 = xstrdup(moab_tasklist);
	tok = strtok_r(tmp1, ":", &tok_p);
	while (tok) {

		tmp2 = strchr(tok, (int) '*');
		if (tmp2) {
			reps = atoi(tmp2 + 1);
			tmp2[0] = '\0';
		} else
			reps = 1;


		hl = hostlist_create(tok);
		while ((host = hostlist_shift(hl))) {
			for (i=0; i<reps; i++) {
				if (slurm_tasklist[0])
					xstrcat(slurm_tasklist, ",");
				xstrcat(slurm_tasklist, host);
				if (!cr_enabled)
					break;
			}
			free(host);
			(*task_cnt) += reps;
		}
		hostlist_destroy(hl);


		tok = strtok_r(NULL, ":", &tok_p);
	}
	xfree(tmp1);
	return slurm_tasklist;
}
