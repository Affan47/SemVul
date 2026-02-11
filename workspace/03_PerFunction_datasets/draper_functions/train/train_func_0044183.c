read_data (unsigned char* pixels,unsigned char* palette)
{
	png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

	for (size_t j=0;j<nHeight;j++)
	{
		memcpy (pixels+j*nChannels*nWidth,row_pointers[j],nChannels*nWidth);
	}
	if (bHasPalette && palette)
	{
		int n;
		png_colorp png_matricePalette;
		png_get_PLTE (png_ptr,info_ptr,&png_matricePalette,&n);
		for (int j=0;j<n;j++)
		{
			palette[j*3+0] = png_matricePalette[j].red;
			palette[j*3+1] = png_matricePalette[j].green;
			palette[j*3+2] = png_matricePalette[j].blue;
		}
	}
}
