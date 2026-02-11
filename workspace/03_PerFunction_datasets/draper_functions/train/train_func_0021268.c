check(int n, unsigned h, unsigned s, unsigned c, sector_t start)
{
	sector_t total, real_s, real_c;

	real_s = sector(s) - 1;
	real_c = cylinder(s, c);
	total = (real_c * g_sectors + real_s) * g_heads + h;
	if (!total)
		printf("Partition %u contains sector 0\n", n);
	if (h >= g_heads)
		printf("Partition %u: head %u greater than maximum %u\n",
			n, h + 1, g_heads);
	if (real_s >= g_sectors)
		printf("Partition %u: sector %u greater than "
			"maximum %u\n", n, s, g_sectors);
	if (real_c >= g_cylinders)
		printf("Partition %u: cylinder %"SECT_FMT"u greater than "
			"maximum %u\n", n, real_c + 1, g_cylinders);
	if (g_cylinders <= 1024 && start != total)
		printf("Partition %u: previous sectors %"SECT_FMT"u disagrees with "
			"total %"SECT_FMT"u\n", n, start, total);
}
