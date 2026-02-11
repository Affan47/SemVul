charset_read_header(FILE *file, struct charset_header *header)
{
	if (fread(header->version, sizeof(header->version), 1, file) != 1 ||
	    fread(header->check, sizeof(header->check), 1, file) != 1)
		return -1;
	{
		unsigned char values[4];
		if (fread(values, sizeof(values), 1, file) != 1)
			return -1;
		header->min = values[0];
		header->max = values[1];
		header->length = values[2];
		header->count = values[3];
	}
	return
	    fread(header->offsets, sizeof(header->offsets), 1, file) != 1 ||
	    fread(header->order, sizeof(header->order), 1, file) != 1;
}
