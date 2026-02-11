ioat_update_pending(struct ioatdma_chan *ioat_chan)
{
	if (ioat_ring_pending(ioat_chan) > ioat_pending_level)
		__ioat_issue_pending(ioat_chan);
}
