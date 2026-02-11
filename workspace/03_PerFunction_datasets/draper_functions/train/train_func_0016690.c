fswc_add_image_bgr32(src_t *src, avgbmp_t *abitmap)
{
	uint8_t *img = (uint8_t *) src->img;
	uint32_t p, i = src->width * src->height;

	if(src->length << 2 < i) return(-1);

	for(p = 0; p < i; p += 4)
	{
		abitmap[0] += img[2];
		abitmap[1] += img[1];
		abitmap[2] += img[0];
		abitmap += 3;
		img += 4;
	}

	return(0);
}
