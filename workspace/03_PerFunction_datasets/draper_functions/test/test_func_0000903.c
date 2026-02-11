ftrace_update_code(struct module *mod, struct ftrace_page *new_pgs)
{
	struct ftrace_page *pg;
	struct dyn_ftrace *p;
	cycle_t start, stop;
	unsigned long update_cnt = 0;
	unsigned long ref = 0;
	bool test = false;
	int i;


	if (mod) {
		struct ftrace_ops *ops;

		for (ops = ftrace_ops_list;
		     ops != &ftrace_list_end; ops = ops->next) {
			if (ops->flags & FTRACE_OPS_FL_ENABLED) {
				if (ops_traces_mod(ops))
					ref++;
				else
					test = true;
			}
		}
	}

	start = ftrace_now(raw_smp_processor_id());

	for (pg = new_pgs; pg; pg = pg->next) {

		for (i = 0; i < pg->index; i++) {
			int cnt = ref;


			if (unlikely(ftrace_disabled))
				return -1;

			p = &pg->records[i];
			if (test)
				cnt += referenced_filters(p);
			p->flags = cnt;


			if (!ftrace_code_disable(mod, p))
				break;

			update_cnt++;


			if (ftrace_start_up && cnt) {
				int failed = __ftrace_replace_code(p, 1);
				if (failed)
					ftrace_bug(failed, p);
			}
		}
	}

	stop = ftrace_now(raw_smp_processor_id());
	ftrace_update_time = stop - start;
	ftrace_update_tot_cnt += update_cnt;

	return 0;
}
