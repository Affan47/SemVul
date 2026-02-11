set_rgb_color_val(unsigned char *start, uint32 val, unsigned char mod)
{
	unsigned char r = val, g = val >> 8, b = val >> 16;
	start[0] = ( r > mod ) ? (r - mod) : 1;
	start[1] = ( g > mod ) ? (g - mod) : 1;
	start[2] = ( b > mod ) ? (b - mod) : 1;
}
