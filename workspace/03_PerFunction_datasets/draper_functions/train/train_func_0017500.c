get_crash_notes(int cpu, uint64_t *addr, uint64_t *len)
{
	const char *crash_notes = "/sys/kernel/crash_notes";
	char line[MAX_LINE];
	FILE *fp;
	unsigned long vaddr;
	int count;

	fp = fopen(crash_notes, "r");
	if (fp) {
		if (fgets(line, sizeof(line), fp) != 0) {
			count = sscanf(line, "%lx", &vaddr);
			if (count != 1)
				die("Cannot parse %s: %s\n", crash_notes,
						strerror(errno));
		}

		*addr = x86__pa(vaddr + (cpu * MAX_NOTE_BYTES));
		*len = MAX_NOTE_BYTES;
#ifdef DEBUG
		printf("crash_notes addr = %Lx\n", *addr);
#endif
		fclose(fp);
		return 0;
	} else
		return get_crash_notes_per_cpu(cpu, addr, len);
}
