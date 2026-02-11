loadData(png_structp png_ptr, int depth)

{
	png_bytep *row_pointers = new png_bytep[height];
	data = new unsigned char[width*height*depth];

	for (unsigned int i=0; i<height; i++)
		row_pointers[height-1-i]=data + i*width*depth;

	png_read_image(png_ptr, row_pointers);
	delete [] row_pointers;
}
