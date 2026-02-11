lpfc_wwn_set(const char *buf, size_t cnt, char wwn[])
{
	unsigned int i, j;


	if (buf[cnt-1] == '\n')
		cnt--;

	if ((cnt < 16) || (cnt > 18) || ((cnt == 17) && (*buf++ != 'x')) ||
	    ((cnt == 18) && ((*buf++ != '0') || (*buf++ != 'x'))))
		return -EINVAL;

	memset(wwn, 0, WWN_SZ);


	for (i = 0, j = 0; i < 16; i++) {
		if ((*buf >= 'a') && (*buf <= 'f'))
			j = ((j << 4) | ((*buf++ - 'a') + 10));
		else if ((*buf >= 'A') && (*buf <= 'F'))
			j = ((j << 4) | ((*buf++ - 'A') + 10));
		else if ((*buf >= '0') && (*buf <= '9'))
			j = ((j << 4) | (*buf++ - '0'));
		else
			return -EINVAL;
		if (i % 2) {
			wwn[i/2] = j & 0xff;
			j = 0;
		}
	}
	return 0;
}
