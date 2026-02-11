ipmi_sel_oem_readval(char *str)
{
	int ret;
	if (!strcmp(str, "XX")) {
		return -1;
	}
	if (!strcmp(str, "R")) {
		return -2;
	}
	if (sscanf(str, "0x%x", &ret) != 1) {
		return -3;
	}
	return ret;
}
