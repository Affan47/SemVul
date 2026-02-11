mxser_request_vector(struct mxser_board *brd)
{
	if (mxser_overlapping_vector(brd))
		return 0;
	return request_region(brd->vector, 1, "mxser(vector)") ? 0 : -EIO;
}
