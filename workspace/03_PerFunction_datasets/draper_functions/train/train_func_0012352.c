cavan_mtd_show_parts_info(const struct mtd_partition_info *parts, size_t size)
{
	const struct mtd_partition_info *part_end;

	for (part_end = parts + size; parts < part_end; parts++)
	{
		print("name = \"%s\", index = %02d, ", parts->name, parts->index);
		print("erase_size = %s, ", size2text(parts->erase_size));
		println("total_size = %s", size2text(parts->size));
	}
}
