nes_free_cqp_request(struct nes_device *nesdev,
			  struct nes_cqp_request *cqp_request)
{
	unsigned long flags;

	nes_debug(NES_DBG_CQP, "CQP request %p (opcode 0x%02X) freed.\n",
		  cqp_request,
		  le32_to_cpu(cqp_request->cqp_wqe.wqe_words[NES_CQP_WQE_OPCODE_IDX]) & 0x3f);

	if (cqp_request->dynamic) {
		kfree(cqp_request);
	} else {
		spin_lock_irqsave(&nesdev->cqp.lock, flags);
		list_add_tail(&cqp_request->list, &nesdev->cqp_avail_reqs);
		spin_unlock_irqrestore(&nesdev->cqp.lock, flags);
	}
}
