sas_parse_addr(u8 *sas_addr, const char *p)
{
	int i;
	for (i = 0; i < SAS_ADDR_SIZE; i++) {
		u8 h, l;
		if (!*p)
			break;
		h = isdigit(*p) ? *p-'0' : toupper(*p)-'A'+10;
		p++;
		l = isdigit(*p) ? *p-'0' : toupper(*p)-'A'+10;
		p++;
		sas_addr[i] = (h<<4) | l;
	}
}
