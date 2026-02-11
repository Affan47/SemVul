topPixelY(int64_t x, int64_t bboxTop, int B)
{
	if ((x % (4*B)) == 0)
		return ceildiv(bboxTop, 2*B) * 2*B;
	return ceildiv(bboxTop - B, 2*B) * 2*B + B;
}
