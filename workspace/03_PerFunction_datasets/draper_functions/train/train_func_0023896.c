dgnc_vpd_show(struct device *p, struct device_attribute *attr,
			     char *buf)
{
	struct dgnc_board *bd;
	int count = 0;
	int i = 0;

	DGNC_VERIFY_BOARD(p, bd);

	count += sprintf(buf + count,
		"\n      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
	for (i = 0; i < 0x40 * 2; i++) {
		if (!(i % 16))
			count += sprintf(buf + count, "\n%04X ", i * 2);
		count += sprintf(buf + count, "%02X ", bd->vpd[i]);
	}
	count += sprintf(buf + count, "\n");

	return count;
}
