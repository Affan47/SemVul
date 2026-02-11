center_put_to_buffer(char* dest, int destPitch, int x1, int y1, int x2, int y2, char *desStr)
{
	int tx = x1 + ((x2-x1) - text_width(desStr))/2;
   int ty = y1 + ((y2-y1) - font_height)/2;

   if( tx<0 )
		tx=0;

   put_to_buffer( dest, destPitch, tx, ty, desStr);
}
