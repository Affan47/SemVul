v4lconvert_hflip_yuv420(unsigned char *src, unsigned char *dest,
		struct v4l2_format *fmt)
{
	int x, y;


	for (y = 0; y < fmt->fmt.pix.height; y++) {
		src += fmt->fmt.pix.width;
		for (x = 0; x < fmt->fmt.pix.width; x++)
			*dest++ = *--src;
		src += fmt->fmt.pix.bytesperline;
	}


	for (y = 0; y < fmt->fmt.pix.height / 2; y++) {
		src += fmt->fmt.pix.width / 2;
		for (x = 0; x < fmt->fmt.pix.width / 2; x++)
			*dest++ = *--src;
		src += fmt->fmt.pix.bytesperline / 2;
	}


	for (y = 0; y < fmt->fmt.pix.height / 2; y++) {
		src += fmt->fmt.pix.width / 2;
		for (x = 0; x < fmt->fmt.pix.width / 2; x++)
			*dest++ = *--src;
		src += fmt->fmt.pix.bytesperline / 2;
	}
}
