v4lconvert_crop_yuv420(unsigned char *src, unsigned char *dest,
		const struct v4l2_format *src_fmt, const struct v4l2_format *dest_fmt)
{
	int x;
	int startx = ((src_fmt->fmt.pix.width - dest_fmt->fmt.pix.width) / 2) & ~1;
	int starty = ((src_fmt->fmt.pix.height - dest_fmt->fmt.pix.height) / 2) & ~1;
	unsigned char *mysrc = src + starty * src_fmt->fmt.pix.bytesperline + startx;


	for (x = 0; x < dest_fmt->fmt.pix.height; x++) {
		memcpy(dest, mysrc, dest_fmt->fmt.pix.width);
		mysrc += src_fmt->fmt.pix.bytesperline;
		dest += dest_fmt->fmt.pix.bytesperline;
	}


	mysrc = src + src_fmt->fmt.pix.height * src_fmt->fmt.pix.bytesperline +
		(starty / 2) * src_fmt->fmt.pix.bytesperline / 2 + startx / 2;
	for (x = 0; x < dest_fmt->fmt.pix.height / 2; x++) {
		memcpy(dest, mysrc, dest_fmt->fmt.pix.width / 2);
		mysrc += src_fmt->fmt.pix.bytesperline / 2;
		dest += dest_fmt->fmt.pix.bytesperline / 2;
	}


	mysrc = src + src_fmt->fmt.pix.height * src_fmt->fmt.pix.bytesperline * 5 / 4
		+ (starty / 2) * src_fmt->fmt.pix.bytesperline / 2 + startx / 2;
	for (x = 0; x < dest_fmt->fmt.pix.height / 2; x++) {
		memcpy(dest, mysrc, dest_fmt->fmt.pix.width / 2);
		mysrc += src_fmt->fmt.pix.bytesperline / 2;
		dest += dest_fmt->fmt.pix.bytesperline / 2;
	}
}
