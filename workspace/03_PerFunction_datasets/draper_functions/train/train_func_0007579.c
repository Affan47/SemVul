setup_file_all(char *filename, SyroData *syro_data)
{
	uint32_t size;

	syro_data->pData = read_file(filename, &size);
	if (!syro_data->pData) {
		return false;
	}

	syro_data->Size = size;

	printf ("ok.\n");

	return true;
}
