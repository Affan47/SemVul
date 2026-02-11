get_cpu_statistics(struct stats_cpu *cpu, data_t *up, data_t *up0)
{
	FILE *fp;
	char buf[1024];

	fp = xfopen_for_read(PROCFS_STAT);

	while (fgets(buf, sizeof(buf), fp)) {
		data_t sum;
		unsigned cpu_number;
		struct stats_cpu *cp;

		if (!starts_with_cpu(buf))
			continue;

		cp = cpu;
		if (buf[3] != ' ') {

			if (G.cpu_nr == 0
			 || sscanf(buf + 3, "%u ", &cpu_number) != 1
			 || cpu_number >= G.cpu_nr
			) {
				continue;
			}
			cp = &cpu[cpu_number + 1];
		}


		memset(cp, 0, sizeof(*cp));
		sscanf(buf, "%*s"
			" %"FMT_DATA"u %"FMT_DATA"u %"FMT_DATA"u"
			" %"FMT_DATA"u %"FMT_DATA"u %"FMT_DATA"u"
			" %"FMT_DATA"u %"FMT_DATA"u %"FMT_DATA"u",
			&cp->cpu_user, &cp->cpu_nice, &cp->cpu_system,
			&cp->cpu_idle, &cp->cpu_iowait, &cp->cpu_irq,
			&cp->cpu_softirq, &cp->cpu_steal, &cp->cpu_guest
		);


		sum = cp->cpu_user + cp->cpu_nice + cp->cpu_system +
			cp->cpu_idle + cp->cpu_iowait + cp->cpu_irq +
			cp->cpu_softirq + cp->cpu_steal;

		if (buf[3] == ' ') {

			*up = sum;
		} else {

			if (cpu_number == 0 && *up0 != 0) {

				*up0 = sum;
			}
		}
	}
	fclose(fp);
}
