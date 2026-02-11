nvram_handler_mjkjidai(mame_file *file, int read_or_write)
{
	if (read_or_write)
		mame_fwrite(file, nvram, nvram_size);
	else if (file)
		mame_fread(file, nvram, nvram_size);
	else
	{
		nvram_init_count = 1;
	}
}
