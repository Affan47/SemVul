list_table(list_t list_type)
{
	partinfo_t info;
	geometry_t geo;
	int i, w = 0;

	update_units(part);
	part_getgeometry(part, &geo);

	printf("\nDisk %s: %d heads, %d sectors, %d cylinders\n",
	       device, geo.heads, geo.sectors, geo.cylinders);

	if (list_type == LIST_NORMAL) {
		printf("Units = %ss of ",
		       unit_flag ? "cylinder" : "sector");
		if (display_factor > 1)
			printf("%d * ", display_factor);
		printf("512 bytes\n\n");

		w = strlen(device) + 1;
		if (w < 6)
			w = 6;

		printf("%*s Boot   Begin    Start      End   Blocks     Id   System\n",
		       w, "Device");
	} else
		printf("Nr AF  Hd Sec  Cyl  Hd Sec  Cyl   Start    Size ID\n");

	i = 0;
	while (part_getpartinfo(part, i++, &info)) {
		if (list_type == LIST_NORMAL && !is_displayable_partition(info.type))
			continue;

		if (list_type == LIST_NORMAL) {
			printf("%*s%-2d  %c%9d%9d%9d%11llu%c  %4x  %s\n",
			       w - 1, device, info.kern_part_no, ' ',
			       sectors_to_units(calculate(part, info.chs_start.head,
						      info.chs_start.sector,
						      info.chs_start.cylinder)),
			       sectors_to_units(info.blk_start),
			       sectors_to_units(info.blk_end + (info.blk_end & 1 ? 0 : 1)),
			       (unsigned long long)((info.blk_end - info.blk_start + 1) / 2),
			       (info.blk_end - info.blk_start + 1) & 1 ? '+' : ' ',
			       info.type,
			       part_typename(part, info.type));

		} else {
			printf("%2d %02x%4d%4d%5d%4d%4d%5d%12llu%12llu %03x\n",
			       info.kern_part_no, 0, info.chs_start.head,
			       info.chs_start.sector, info.chs_start.cylinder,
			       info.chs_end.head, info.chs_end.sector,
			       info.chs_end.cylinder,
			       (unsigned long long)info.blk_start,
			       (unsigned long long)(info.blk_end - info.blk_start + 1),
			       info.type);


		}
	}
}
