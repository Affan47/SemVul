compute_gap(struct params *fd, int track_size)
{
	int gap;

	gap = (fd->raw_capacity-track_size)*track_size/GAP_DIVISOR-header_size;
	if (gap > 0x6c * 32)


		gap = 0x6c * 32;
	if (gap < 0)
		gap = 0;
	return gap;
}
