report_match(struct searchinfo *si, ulong addr, char *ptr1, int len1, char *ptr2, int len2)
{
	int i;

	if (si->do_task_header) {
		print_task_header(fp, si->task_context, si->tasks_found);
		si->do_task_header = FALSE;
		si->tasks_found++;
	}

	fprintf(fp, "%lx: ", addr);
	for (i = 0; i < len1; i++) {
		if (isprint(ptr1[i]))
			fprintf(fp, "%c", ptr1[i]);
		else
			fprintf(fp, ".");
	}
	for (i = 0; i < len2; i++) {
		if (isprint(ptr2[i]))
			fprintf(fp, "%c", ptr2[i]);
		else
			fprintf(fp, ".");
	}
	fprintf(fp, "\n");
}
