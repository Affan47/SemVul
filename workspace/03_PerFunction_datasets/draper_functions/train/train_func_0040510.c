rom_fread(struct rom_load_data *romdata, UINT8 *buffer, int length)
{

	if (romdata->file)
		return mame_fread(romdata->file, buffer, length);


	else
		fill_random(buffer, length);

	return length;
}
