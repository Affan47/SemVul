add_scan_results()
{
	int index;
	char cmd[20];

	index = 0;
	while (wpagui) {
		snprintf(cmd, sizeof(cmd), "BSS %d", index++);
		if (index > 1000)
			break;

		if (!add_bss(cmd))
			break;
	}
}
