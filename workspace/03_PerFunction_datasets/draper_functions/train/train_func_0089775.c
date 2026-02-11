get_events(timer_stat_t *timer_stats[])
{
	FILE *fp;
	char buf[4096];

	if ((fp = fopen(TIMER_STATS, "r")) == NULL) {
		fprintf(stderr, "Cannot open %s\n", TIMER_STATS);
		return;
	}


	while (!feof(fp)) {
		char *ptr = buf;
		unsigned long count = -1;
		pid_t pid = -1;
		char task[64];
		char func[128];
		char timer[128];
		bool kernel_thread;
		int mask;

		if (fgets(buf, sizeof(buf), fp) == NULL)
			break;

		if (strstr(buf, "total events") != NULL)
			break;

		if (strstr(buf, ",") == NULL)
			continue;


		while (*ptr && *ptr != ',')
			ptr++;

		if (*ptr != ',')
			continue;

		if (ptr > buf && *(ptr-1) == 'D')
			continue;

		ptr++;
		sscanf(buf, "%21lu", &count);
		memset(task, 0, sizeof(task));
		memset(func, 0, sizeof(func));
		memset(timer, 0, sizeof(timer));
		if (sscanf(ptr, "%10d %63s %127s (%127[^)])", &pid, task, func, timer) != 4)
			continue;

		kernel_thread = pid_a_kernel_thread(task, pid);


		if (strncmp(task, "swapper", 6) == 0)
			kernel_thread = true;

		mask = kernel_thread ? OPT_KERNEL : OPT_USER;

		if (!(opt_flags & mask))
			continue;

		if (kernel_thread) {
			char tmp[64];
			task[13] = '\0';
			snprintf(tmp, sizeof(tmp), "[%s]", task);
			strcpy(task, tmp);
		}

		if (strcmp(task, "insmod") == 0)
			strcpy(task, "[kern mod]");
		if (strcmp(task, "modprobe") == 0)
			strcpy(task, "[kern mod]");

		if ((strncmp(func, "tick_nohz_", 10) == 0) ||
		    (strncmp(func, "tick_setup_sched_timer", 20) == 0) ||
		    (strcmp(task, APP_NAME) == 0))
			continue;

		timer_stat_add(timer_stats, count, pid, task, func, timer, kernel_thread);
	}

	fclose(fp);
}
