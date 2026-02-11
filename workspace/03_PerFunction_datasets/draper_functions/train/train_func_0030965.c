cavan_mtd_get_partition_info_by_name(struct cavan_mtd_descriptor *desc, const char *partname)
{
	struct mtd_partition_info *p, *p_end;

	for (p = desc->part_infos, p_end = p + desc->part_count; p < p_end; p++)
	{
		if (text_cmp(p->name, partname) == 0)
		{
			return p;
		}
	}

	return NULL;
}
