xhci_free_stream_info(struct xhci_hcd *xhci,
		struct xhci_stream_info *stream_info)
{
	int cur_stream;
	struct xhci_ring *cur_ring;

	if (!stream_info)
		return;

	for (cur_stream = 1; cur_stream < stream_info->num_streams;
			cur_stream++) {
		cur_ring = stream_info->stream_rings[cur_stream];
		if (cur_ring) {
			xhci_ring_free(xhci, cur_ring);
			stream_info->stream_rings[cur_stream] = NULL;
		}
	}
	xhci_free_command(xhci, stream_info->free_streams_command);
	xhci->cmd_ring_reserved_trbs--;
	if (stream_info->stream_ctx_array)
		xhci_free_stream_ctx(xhci,
				stream_info->num_stream_ctxs,
				stream_info->stream_ctx_array,
				stream_info->ctx_array_dma);

	kfree(stream_info->stream_rings);
	kfree(stream_info);
}
