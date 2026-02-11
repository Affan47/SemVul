update_header(FILE *f)
{
	off_t cur, end;
	uint32_t datalen;
	int bytes;

	cur = ftell(f);
	fseek(f, 0, SEEK_END);
	end = ftell(f);

	bytes = end - AU_HEADER_SIZE;
	datalen = htoll(bytes);

	if (cur < 0) {
		ast_log(LOG_WARNING, "Unable to find our position\n");
		return -1;
	}
	if (fseek(f, AU_HDR_DATA_SIZE_OFF * sizeof(uint32_t), SEEK_SET)) {
		ast_log(LOG_WARNING, "Unable to set our position\n");
		return -1;
	}
	if (fwrite(&datalen, 1, sizeof(datalen), f) != sizeof(datalen)) {
		ast_log(LOG_WARNING, "Unable to set write file size\n");
		return -1;
	}
	if (fseek(f, cur, SEEK_SET)) {
		ast_log(LOG_WARNING, "Unable to return to position\n");
		return -1;
	}
	return 0;
}
