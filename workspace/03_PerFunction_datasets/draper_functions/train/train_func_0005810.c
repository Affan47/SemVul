random_get32(void)
{
	FILE *fp = fopen("/dev/urandom", "rb");
	if (!fp) {
		return (uint32_t)getcurrenttime();
	}

	uint32_t Result;
	if (fread(&Result, 4, 1, fp) != 1) {
		Result = (uint32_t)getcurrenttime();
	}

	fclose(fp);
	return Result;
}
