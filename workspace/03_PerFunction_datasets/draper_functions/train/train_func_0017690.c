get_cpu_statistics(struct stats_cpu *sc)
{
	FILE *fp;
	char buf[1024];

	fp = xfopen_for_read("/proc/stat");

	memset(sc, 0, sizeof(*sc));

	while (fgets(buf, sizeof(buf), fp)) {

		if (starts_with_cpu(buf) && buf[3] == ' ') {
			sscanf(buf + 4 + 1,
				"%"FMT_DATA"u %"FMT_DATA"u %"FMT_DATA"u %"FMT_DATA"u %"
				FMT_DATA"u %"FMT_DATA"u %"FMT_DATA"u %"FMT_DATA"u %"FMT_DATA"u",
				&sc->cpu_user, &sc->cpu_nice, &sc->cpu_system,
				&sc->cpu_idle, &sc->cpu_iowait, &sc->cpu_irq,
				&sc->cpu_softirq, &sc->cpu_steal, &sc->cpu_guest);
		}
	}

	fclose(fp);
}
