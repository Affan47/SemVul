jfs_proc_clean(void)
{
	int i;

	if (base) {
		for (i = 0; i < NPROCENT; i++)
			remove_proc_entry(Entries[i].name, base);
		remove_proc_entry("fs/jfs", NULL);
	}
}
