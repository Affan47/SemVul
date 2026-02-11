cas_vpd_match(const void __iomem *p, const char *str)
{
	int len = strlen(str) + 1;
	int i;

	for (i = 0; i < len; i++) {
		if (readb(p + i) != str[i])
			return 0;
	}
	return 1;
}
