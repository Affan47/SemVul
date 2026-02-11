write_file(char *filename, uint8_t *buf, uint32_t size)
{
	FILE *fp;

	fp = fopen(filename, "wb");
	if (!fp) {
		printf (" File open error, %s \n", filename);
		return false;
	}

	if (fwrite(buf, 1, size, fp) < size) {
		printf (" File write error(perhaps disk space is not enough), %s \n", filename);
		fclose(fp);
		return false;
	}

	fclose(fp);

	return true;
}
