CopyExternalWithoutAdjustments(void)
{
	int i;
	unsigned char *ext_ptr;
	for (i = 0, ext_ptr = Colours_external->palette; i < 256; i ++, ext_ptr += 3)
		Colours_SetRGB(i, *ext_ptr, *(ext_ptr + 1), *(ext_ptr + 2), Colours_table);
}
