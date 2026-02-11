mapQualityToVP8QP(int quality) {
#define MIN_QUALITY 0
#define MAX_QUALITY 100
#define MIN_VP8QP 1
#define MAX_VP8QP 63
	const float scale = MAX_VP8QP - MIN_VP8QP;
	const float vp8qp =
	scale * (MAX_QUALITY - quality) / (MAX_QUALITY - MIN_QUALITY) + MIN_VP8QP;
	if (quality < MIN_QUALITY || quality > MAX_QUALITY) {
		gd_error("Wrong quality value %d.", quality);
		return -1;
	}

	return (int)(vp8qp + 0.5);
}
