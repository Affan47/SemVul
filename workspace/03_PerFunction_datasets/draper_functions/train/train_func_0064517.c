hpav_init_write_data_request(void *buf, int len, void *UNUSED(buffer))
{
	int avail = len;
	struct write_mod_data_request *mm = buf;
	char filename[256];
	char *buffer;
	FILE *fp;
	short unsigned int size;
	uint32_t crc32;

	faifa_printf(out_stream, "Module ID? ");
	fscanf(in_stream, "%2hx", (short unsigned int *)&(mm->module_id));
	faifa_printf(out_stream, "Offset? ");
	fscanf(in_stream, "%8lx", (long unsigned int *)&(mm->offset));
	faifa_printf(out_stream, "Firmware file? ");
	fscanf(in_stream, "%s", (char *)filename);
	fp = fopen(filename, "rb");
	if (!fp) {
		faifa_printf(err_stream, "Cannot open: %s\n", filename);
		avail = -1;
		goto out;
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	if (size > 1024) {
		faifa_printf(out_stream, "Invalid file size > 1024\n");
		avail = -1;
		goto out;
	}
	fseek(fp, 0, SEEK_SET);
	mm->length = size;
	buffer = malloc(size);
	if (!buffer) {
		faifa_printf(err_stream, "Cannot allocate memory\n");
		avail = -1;
		goto out;
	}
	fread(buffer, size, 1, fp);

	crc32 = crc32buf(buffer, size);
	memcpy(&(mm->data), buffer, size);
	mm->checksum = crc32;
out:
	if (fp)
		fclose(fp);
	avail -= sizeof(*mm);
	return (len - avail);
}
