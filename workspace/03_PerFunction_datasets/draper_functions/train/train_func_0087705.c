dumb_start_resampler_n(int n, void *src, int src_channels, long pos, long start, long end)
{
	if (n == 8)
		return dumb_start_resampler_8(src, src_channels, pos, start, end);
	else if (n == 16)
		return dumb_start_resampler_16(src, src_channels, pos, start, end);
	else
		return dumb_start_resampler(src, src_channels, pos, start, end);
}
