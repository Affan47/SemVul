genwqe_read_app_id(struct genwqe_dev *cd, char *app_name, int len)
{
	int i, j;
	u32 app_id = (u32)cd->app_unitcfg;

	memset(app_name, 0, len);
	for (i = 0, j = 0; j < min(len, 4); j++) {
		char ch = (char)((app_id >> (24 - j*8)) & 0xff);

		if (ch == ' ')
			continue;
		app_name[i++] = isprint(ch) ? ch : 'X';
	}
	return i;
}
