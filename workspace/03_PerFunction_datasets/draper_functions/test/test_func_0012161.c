diskdump_memory_dump(FILE *fp)
{
	int i;

	if (KDUMP_SPLIT() && (dd_list != NULL))
		for (i = 0; i < num_dumpfiles; i++) {
			dd = dd_list[i];
			__diskdump_memory_dump(fp);
			fprintf(fp, "\n");
		}
	else
		__diskdump_memory_dump(fp);

	return 0;
}
