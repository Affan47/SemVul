is_dma_done(struct cobalt_stream *s)
{
	struct cobalt *cobalt = s->cobalt;

	if (ioread32(CS_REG(s->dma_channel)) & DONE)
		return true;

	return false;
}
