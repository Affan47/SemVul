usbhsf_dma_push_done(struct usbhs_pkt *pkt, int *is_done)
{
	struct usbhs_pipe *pipe = pkt->pipe;
	int is_short = pkt->trans % usbhs_pipe_get_maxpacket(pipe);

	pkt->actual += pkt->trans;

	if (pkt->actual < pkt->length)
		*is_done = 0;
	else if (is_short)
		*is_done = 1;
	else
		*is_done = !pkt->zero;

	usbhs_pipe_running(pipe, !*is_done);

	usbhsf_dma_stop(pipe, pipe->fifo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fifo_unselect(pipe, pipe->fifo);

	if (!*is_done) {

		pkt->handler = &usbhs_fifo_pio_push_handler;
		return pkt->handler->try_run(pkt, is_done);
	}

	return 0;
}
