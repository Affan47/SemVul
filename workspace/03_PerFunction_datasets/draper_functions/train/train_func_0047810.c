create_disk_image(void)
{
	int maxspt = (sizeMB <= BAR32G) ? MaxSPT : MAXSPT;

	int cyl = sizeMB * 2048 / MAXHEADS / maxspt;
	if (cyl > MAXCYLS) cyl = MAXCYLS;
	long sectors = cyl * MAXHEADS * maxspt;
	bool ret = make_image(sectors, cdi_path);
	UpdateDiskParameters(cdi_disk, true);
	return ret;
}
