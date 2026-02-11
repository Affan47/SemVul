bitmap_c64_type(char* file)
{
	BitmapType type = C64_BITMAPS;

	FILE* f = fopen(file,"rb");
	if (f != NULL)
	{
		L9UINT32 size = filelength(f);
		fclose(f);

		if (size == 10048)
			type = BBC_BITMAPS;
		if (size == 6494)
			type = BBC_BITMAPS;
	}

	return type;
}
