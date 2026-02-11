qtree_entry_unused(struct qtree_mem_dqinfo *info, char *disk)
{
	int i;

	for (i = 0; i < info->dqi_entry_size; i++)
		if (disk[i])
			return 0;
	return 1;
}
