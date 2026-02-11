put_bitmap_remap(int x,int y,char* bitmapPtr,char *colorTable)
{
	err_when( !buf_locked );

	if( is_front )
		mouse.hide_area( x, y, x+*((short*)bitmapPtr)-1, y+*(((short*)bitmapPtr)+1)-1 );

	IMGbltRemap(buf_ptr(), buf_pitch(), x, y, bitmapPtr, colorTable);

	if( is_front )
		mouse.show_area();
}
