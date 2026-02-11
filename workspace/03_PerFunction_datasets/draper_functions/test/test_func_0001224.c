scanline_diff(const unsigned char *scanlines, int prev, int cur)
{
	const unsigned char *line1 = scanlines + prev * VFS301_FP_OUTPUT_WIDTH;
	const unsigned char *line2 = scanlines + cur * VFS301_FP_OUTPUT_WIDTH;
	int i;
	int diff;

#ifdef OUTPUT_RAW

	line1 = ((vfs301_line_t*)line1)->scan;
	line2 = ((vfs301_line_t*)line2)->scan;
#endif


	for (diff = 0, i = 0; i < VFS301_FP_WIDTH; i++) {
		if (*line1 > *line2)
			diff += *line1 - *line2;
		else
			diff += *line2 - *line1;

		line1++;
		line2++;
	}

	return ((diff / VFS301_FP_WIDTH) > VFS301_FP_LINE_DIFF_THRESHOLD);
}
