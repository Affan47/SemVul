draw_step(short left, short bottom, VgaBuf *vgabuf, short wind)
{

	unsigned char *p;
	unsigned char *d;
	short x,y;
	for( x=0; x < map_width; ++x)
	{
		y = map_height-2;
		p = heat_map + y*map_width + x;
		d = (unsigned char *)vgabuf->buf_ptr() +
			(bottom-y)*vgabuf->buf_pitch() + left + x;
		for( ; y >= 0; --y, p-=map_width, d+=vgabuf->buf_pitch() )
		{
			unsigned char v = *p;
			if(  v < decay || x <= 0 || x >= map_width-1)
			{
				p[map_width] = 0;
			}
			else
			{
				unsigned char n = v - random(decay);
				p[map_width -random(3)+1  + wind*random(2)] = n;

				*d = shade_base + 0x0f - ( n >> 4);
			}
		}
	}
}
