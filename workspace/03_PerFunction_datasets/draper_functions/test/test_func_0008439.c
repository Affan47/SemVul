faifa_sprint_hex(char *str, void *buf, int len, char *sep)
{
	int avail = len;
	u_int8_t *pbuf = buf;
	char *pstr = str;

	while (avail > 0) {
		pstr += sprintf((char *)pstr, "%02hX%s", (unsigned short int)*pbuf, (avail > 1) ? sep : "");
		pbuf++;
		avail--;
	}

	return (pstr - str);
}
