bin2cap(buf, c)
char *buf;
int c;
{
	int i;

	i = 0;
	if (c < 0x80) buf[i++] = c;
	else {
		buf[i++] = ':';
		buf[i++] = tohexa((c >> 4) & 0xf);
		buf[i++] = tohexa(c & 0xf);
	}

	return(i);
}
