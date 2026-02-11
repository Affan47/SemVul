ttip_desaturate(ttip_image_t* output, ttip_image_t source) {
	ttip_format_t dstformat;
	int srcstep, dststep;

	switch (source->format) {
	case TTIP_GRAY:
	case TTIP_GRAY_ALPHA:
		return ttip_clone(output, source);
	case TTIP_RGB:
		dstformat = TTIP_GRAY;
		srcstep = 3;
		dststep = 1;
		break;
	case TTIP_RGB_ALPHA:
		dstformat = TTIP_GRAY_ALPHA;
		srcstep = 4;
		dststep = 2;
		break;
	default:
		return TTIP_BAD_PIXEL_FORMAT;
	}


	int ret;
	struct ttip_image* destination;
	if ((ret = ttip_create(&destination, source->width, source->height, dstformat)) != TTIP_OK)
		return ret;


	unsigned char *srcrow, *dstrow, *src, *dst;
	for (srcrow = source->data, dstrow = destination->data;
			srcrow < source->data + source->height * source->stride;
			srcrow += source->stride, dstrow += destination->stride) {
		for (src = srcrow, dst = dstrow; src < srcrow + source->width * srcstep; src += srcstep, dst += dststep) {
			*dst = desaturate(src[0], src[1], src[2]);
		}
	}

	*output = destination;

	return TTIP_OK;
}
