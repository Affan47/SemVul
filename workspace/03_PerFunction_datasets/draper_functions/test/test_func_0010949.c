rsxx_dma_cancel(struct rsxx_dma_ctrl *ctrl)
{
	struct rsxx_dma *dma;
	int i;
	int cnt = 0;


	for (i = 0; i < RSXX_MAX_OUTSTANDING_CMDS; i++) {
		dma = get_tracker_dma(ctrl->trackers, i);
		if (dma) {
			atomic_dec(&ctrl->stats.hw_q_depth);
			rsxx_complete_dma(ctrl, dma, DMA_CANCELLED);
			push_tracker(ctrl->trackers, i);
			cnt++;
		}
	}

	return cnt;
}
