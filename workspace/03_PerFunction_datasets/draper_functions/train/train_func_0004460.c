rsxx_dma_destroy(struct rsxx_cardinfo *card)
{
	struct rsxx_dma_ctrl *ctrl;
	int i;

	for (i = 0; i < card->n_targets; i++) {
		ctrl = &card->ctrl[i];

		if (ctrl->issue_wq) {
			destroy_workqueue(ctrl->issue_wq);
			ctrl->issue_wq = NULL;
		}

		if (ctrl->done_wq) {
			destroy_workqueue(ctrl->done_wq);
			ctrl->done_wq = NULL;
		}

		if (timer_pending(&ctrl->activity_timer))
			del_timer_sync(&ctrl->activity_timer);


		spin_lock_bh(&ctrl->queue_lock);
		rsxx_cleanup_dma_queue(ctrl, &ctrl->queue, COMPLETE_DMA);
		spin_unlock_bh(&ctrl->queue_lock);

		rsxx_dma_cancel(ctrl);

		vfree(ctrl->trackers);

		pci_free_consistent(card->dev, STATUS_BUFFER_SIZE8,
				    ctrl->status.buf, ctrl->status.dma_addr);
		pci_free_consistent(card->dev, COMMAND_BUFFER_SIZE8,
				    ctrl->cmd.buf, ctrl->cmd.dma_addr);
	}
}
