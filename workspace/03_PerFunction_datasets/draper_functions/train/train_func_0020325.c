write_stats_core(int prev, int curr, int dis, int disp_avg,
		     char *prev_string, char *curr_string)
{
	unsigned long long itv, g_itv;
	int again = 0;


	TEST_STDOUT(STDOUT_FILENO);


	g_itv = get_interval(uptime[prev], uptime[curr]);

	if (cpu_nr > 1) {

		itv = get_interval(uptime0[prev], uptime0[curr]);
	}
	else {

		itv = g_itv;
	}

	if (DISPLAY_ONELINE(pidflag)) {
		if (DISPLAY_TASK_STATS(tskflag)) {
			again += write_pid_task_all_stats(prev, curr, dis,
						  	 itv, g_itv);
		}
		if (DISPLAY_CHILD_STATS(tskflag)) {
			again += write_pid_child_all_stats(prev, curr, dis, itv);
		}
	}
	else {

		if (DISPLAY_CPU(actflag)) {

			if (DISPLAY_TASK_STATS(tskflag)) {
				again += write_pid_task_cpu_stats(prev, curr, dis, disp_avg,
								  prev_string, curr_string,
								  itv, g_itv);
			}
			if (DISPLAY_CHILD_STATS(tskflag)) {
				again += write_pid_child_cpu_stats(prev, curr, dis, disp_avg,
								   prev_string, curr_string);
			}
		}


		if (DISPLAY_MEM(actflag)) {

			if (DISPLAY_TASK_STATS(tskflag)) {
				again += write_pid_task_memory_stats(prev, curr, dis, disp_avg,
								     prev_string, curr_string, itv);
			}
			if (DISPLAY_CHILD_STATS(tskflag) && DISPLAY_MEM(actflag)) {
				again += write_pid_child_memory_stats(prev, curr, dis, disp_avg,
								      prev_string, curr_string);
			}
		}


		if (DISPLAY_STACK(actflag)) {
			again += write_pid_stack_stats(prev, curr, dis, disp_avg,
						       prev_string, curr_string, itv);
		}


		if (DISPLAY_IO(actflag)) {
			again += write_pid_io_stats(prev, curr, dis, prev_string,
						    curr_string, itv);
		}


		if (DISPLAY_CTXSW(actflag)) {
			again += write_pid_ctxswitch_stats(prev, curr, dis, prev_string,
							   curr_string, itv);
		}


		if (DISPLAY_KTAB(actflag)) {
			again += write_pid_ktab_stats(prev, curr, dis, disp_avg,
						      prev_string, curr_string, itv);
		}
	}

	if (DISPLAY_ALL_PID(pidflag)) {
		again = 1;
	}

	return again;
}
