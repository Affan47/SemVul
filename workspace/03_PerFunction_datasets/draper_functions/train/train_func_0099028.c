fswc_add_image_rgb32(src_t *src, avgbmp_t *abitmap)
{
	uint8_t *img = (uint8_t *) src->img;
	uint32_t i = src->width * src->height;

	if(src->length << 2 < i) return(-1);

	while(i-- > 0)
	{
		*(abitmap++) += *(img++);
		*(abitmap++) += *(img++);
		*(abitmap++) += *(img++);
		img++;
	}

	return(0);
}
