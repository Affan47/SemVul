v4lconvert_yuyv_to_yuv420(const unsigned char *src, unsigned char *dest,
		int width, int height, int stride, int yvu)
{
	int i, j;
	const unsigned char *src1;
	unsigned char *udest, *vdest;


	src1 = src;
	for (i = 0; i < height; i++) {
		for (j = 0; j + 1 < width; j += 2) {
			*dest++ = src1[0];
			*dest++ = src1[2];
			src1 += 4;
		}
		src1 += stride - width * 2;
	}


	src++;
	src1 = src + stride;
	if (yvu) {
		vdest = dest;
		udest = dest + width * height / 4;
	} else {
		udest = dest;
		vdest = dest + width * height / 4;
	}
	for (i = 0; i < height; i += 2) {
		for (j = 0; j + 1 < width; j += 2) {
			*udest++ = ((int) src[0] + src1[0]) / 2;
			*vdest++ = ((int) src[2] + src1[2]) / 2;
			src += 4;
			src1 += 4;
		}
		src1 += stride - width * 2;
		src = src1;
		src1 += stride;
	}
}
