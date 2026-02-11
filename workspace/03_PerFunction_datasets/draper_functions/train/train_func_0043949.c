it821x_display_disk(int n, u8 *buf)
{
	unsigned char id[41];
	int mode = 0;
	const char *mtype = "";
	char mbuf[8];
	const char *cbl = "(40 wire cable)";

	static const char *types[5] = {
		"RAID0", "RAID1", "RAID 0+1", "JBOD", "DISK"
	};

	if (buf[52] > 4)
		return;

	ata_id_c_string((u16 *)buf, id, 0, 41);

	if (buf[51]) {
		mode = ffs(buf[51]);
		mtype = "UDMA";
	} else if (buf[49]) {
		mode = ffs(buf[49]);
		mtype = "MWDMA";
	}

	if (buf[76])
		cbl = "";

	if (mode)
		snprintf(mbuf, 8, "%5s%d", mtype, mode - 1);
	else
		strcpy(mbuf, "PIO");
	if (buf[52] == 4)
		printk(KERN_INFO "%d: %-6s %-8s          %s %s\n",
				n, mbuf, types[buf[52]], id, cbl);
	else
		printk(KERN_INFO "%d: %-6s %-8s Volume: %1d %s %s\n",
				n, mbuf, types[buf[52]], buf[53], id, cbl);
	if (buf[125] < 100)
		printk(KERN_INFO "%d: Rebuilding: %d%%\n", n, buf[125]);
}
