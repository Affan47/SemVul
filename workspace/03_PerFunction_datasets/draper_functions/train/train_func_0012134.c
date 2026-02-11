fluid_rvoice_buffers_check_bufnum(fluid_rvoice_buffers_t* buffers, unsigned int bufnum)
{
	unsigned int i;

	if (bufnum < buffers->count) return FLUID_OK;
	if (bufnum >= FLUID_RVOICE_MAX_BUFS) return FLUID_FAILED;

	for (i = buffers->count; i <= bufnum; i++) {
		buffers->bufs[bufnum].amp = 0.0f;
		buffers->bufs[bufnum].mapping = i;
	}
	buffers->count = bufnum+1;
	return FLUID_OK;
}
