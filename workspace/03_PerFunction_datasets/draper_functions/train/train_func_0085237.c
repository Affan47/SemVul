get_max_streams_for_pipe(struct dummy_hcd *dum_hcd,
		unsigned int pipe)
{
	int max_streams;

	max_streams = dum_hcd->num_stream[usb_pipeendpoint(pipe)];
	if (usb_pipeout(pipe))
		max_streams >>= 4;
	else
		max_streams &= 0xf;
	max_streams++;
	return max_streams;
}
