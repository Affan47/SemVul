get_irqcpu_nr(const char *f, int max_irqs)
{
	FILE *fp;
	char *line;
	unsigned linelen;
	unsigned irq;

	fp = fopen_for_read(f);
	if (!fp)
		return 0;

	linelen = INTERRUPTS_LINE + 16 * G.cpu_nr;
	line = xmalloc(linelen);

	irq = 0;
	while (fgets(line, linelen, fp)
	 && irq < max_irqs
	) {
		int p = strcspn(line, ":");
		if ((p > 0) && (p < 16))
			irq++;
	}

	fclose(fp);
	free(line);

	return irq;
}
