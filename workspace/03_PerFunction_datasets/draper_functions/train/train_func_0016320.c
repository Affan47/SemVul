omni_sg_dma_abort_channel(struct cobalt_stream *s)
{
	struct cobalt *cobalt = s->cobalt;

	if (is_dma_done(s) == false)
		iowrite32(ABORT, CS_REG(s->dma_channel));
}
