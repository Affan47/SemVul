cavan_mtd_free_partition_descriptor(struct mtd_partition_descriptor *desc)
{
	struct cavan_mtd_descriptor *dev_desc = desc->part_info->dev_desc;

	if (desc >= dev_desc->part_descs && (desc - dev_desc->part_descs) < (int) NELEM(dev_desc->part_descs))
	{
		desc->fd = -1;
		desc->part_info = NULL;
	}
	else
	{
		free(desc);
	}
}
