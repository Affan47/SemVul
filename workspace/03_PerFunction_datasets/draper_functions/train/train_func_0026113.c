gen_hexline(const uint8_t *data, uint16_t addr, size_t len, FILE *output)
{
	struct hexline	*hexline;

	if(!data) {
		fprintf(output, ":%02X%04X%02XFF\n", 0, 0, TT_EOF);
		return;
	}
	if((hexline = new_hexline(len, addr, (!data) ? TT_EOF : TT_DATA)) == NULL) {
		if(report_func)
			report_func(LOG_ERR, "No more memory\n");
		return;
	}
	if(data)
		memcpy(&hexline->d.content.tt_data, data, len);
	dump_hexline(0, hexline, output);
	free(hexline);
}
