get_pixel_val16(const uint8_t *pixel, int bpp)
{
	u16 pixel_val16 = 0;
	if (bpp == 2)
		pixel_val16 = *(const uint16_t *)pixel;
	else if (bpp == 4)
		pixel_val16 = pixel32_to_be16(*(const uint32_t *)pixel);
	return pixel_val16;
}
