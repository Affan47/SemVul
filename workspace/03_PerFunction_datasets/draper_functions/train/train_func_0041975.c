new_hexline(uint8_t datalen, uint16_t offset, uint8_t tt)
{
	struct hexline	*hexline;
	size_t		allocsize;

	allocsize = sizeof(struct hexline) + datalen + 1;
	if((hexline = malloc(allocsize)) == NULL) {
		if(report_func)
			report_func(LOG_ERR, "No more memory\n");
		return NULL;
	}
	memset(hexline, 0, allocsize);
	hexline->d.content.header.ll = datalen;
	hexline->d.content.header.offset = offset;
	hexline->d.content.header.tt = tt;
	return hexline;
}
