dundi_ie_append_encdata(struct dundi_ie_data *ied, unsigned char ie, unsigned char *iv, void *data, int datalen)
{
	char tmp[256];
	datalen += 16;
	if (datalen > ((int)sizeof(ied->buf) - ied->pos)) {
		snprintf(tmp, (int)sizeof(tmp), "Out of space for ie '%s' (%d), need %d have %d\n", dundi_ie2str(ie), ie, datalen, (int)sizeof(ied->buf) - ied->pos);
		errorf(tmp);
		return -1;
	}
	ied->buf[ied->pos++] = ie;
	ied->buf[ied->pos++] = datalen;
	memcpy(ied->buf + ied->pos, iv, 16);
	ied->pos += 16;
	if (data) {
		memcpy(ied->buf + ied->pos, data, datalen-16);
		ied->pos += datalen-16;
	}
	return 0;
}
