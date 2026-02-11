put_back(int x, int y, int bitmapId, int compressFlag)
{
	char* bitmapPtr = ResourceIdx::get_data(bitmapId);

	if( bitmapPtr )
	{
		if( compressFlag )
			vga_back.put_bitmap_trans_decompress( x, y, bitmapPtr );
		else
			vga_back.put_bitmap_trans( x, y, bitmapPtr );
	}
}
