read_data_rgba()
{
	format.set_type(pixelformat_rgba);
	format.set_red_mask  (0xff000000);
	format.set_green_mask(0x00ff0000);
	format.set_blue_mask (0x0000ff00);
	format.set_alpha_mask(0x000000ff);

	format.set_depth(32);

	pitch = png_get_rowbytes(png_ptr, info_ptr);


	image = new unsigned char[pitch * height];


	png_bytep* row_pointers = new png_bytep[height];
	{
		for (int y = 0; y < height; y++)
			row_pointers[y] = image + (pitch * y);
	}
	png_read_image(png_ptr, row_pointers);
	delete[] row_pointers;

	if (!CL_Endian::is_system_big())
	{
		for(int y = 0; y < height; ++y)
		{
			unsigned char * line = &image[y * pitch];
			for (int i = 0; i < width * 4; i += 4)
			{
				std::swap(line[i + 0], line[i + 3]);
				std::swap(line[i + 1], line[i + 2]);
			}
		}
	}
}
