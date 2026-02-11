stex_mu_intr(struct st_hba *hba, u32 doorbell)
{
	void __iomem *base = hba->mmio_base;
	struct status_msg *resp;
	struct st_ccb *ccb;
	unsigned int size;
	u16 tag;

	if (unlikely(!(doorbell & MU_OUTBOUND_DOORBELL_STATUSHEADCHANGED)))
		return;


	hba->status_head = readl(base + OMR1);
	if (unlikely(hba->status_head > hba->sts_count)) {
		printk(KERN_WARNING DRV_NAME "(%s): invalid status head\n",
			pci_name(hba->pdev));
		return;
	}


	if (unlikely(hba->out_req_cnt <= 0 ||
			(hba->mu_status == MU_STATE_RESETTING &&
			 hba->cardtype != st_yosemite))) {
		hba->status_tail = hba->status_head;
		goto update_status;
	}

	while (hba->status_tail != hba->status_head) {
		resp = stex_get_status(hba);
		tag = le16_to_cpu(resp->tag);
		if (unlikely(tag >= hba->host->can_queue)) {
			printk(KERN_WARNING DRV_NAME
				"(%s): invalid tag\n", pci_name(hba->pdev));
			continue;
		}

		hba->out_req_cnt--;
		ccb = &hba->ccb[tag];
		if (unlikely(hba->wait_ccb == ccb))
			hba->wait_ccb = NULL;
		if (unlikely(ccb->req == NULL)) {
			printk(KERN_WARNING DRV_NAME
				"(%s): lagging req\n", pci_name(hba->pdev));
			continue;
		}

		size = resp->payload_sz * sizeof(u32);
		if (unlikely(size < sizeof(*resp) - STATUS_VAR_LEN ||
			size > sizeof(*resp))) {
			printk(KERN_WARNING DRV_NAME "(%s): bad status size\n",
				pci_name(hba->pdev));
		} else {
			size -= sizeof(*resp) - STATUS_VAR_LEN;
			if (size)
				stex_copy_data(ccb, resp, size);
		}

		ccb->req = NULL;
		ccb->srb_status = resp->srb_status;
		ccb->scsi_status = resp->scsi_status;

		if (likely(ccb->cmd != NULL)) {
			if (hba->cardtype == st_yosemite)
				stex_check_cmd(hba, ccb, resp);

			if (unlikely(ccb->cmd->cmnd[0] == PASSTHRU_CMD &&
				ccb->cmd->cmnd[1] == PASSTHRU_GET_ADAPTER))
				stex_controller_info(hba, ccb);

			scsi_dma_unmap(ccb->cmd);
			stex_scsi_done(ccb);
		} else
			ccb->req_type = 0;
	}

update_status:
	writel(hba->status_head, base + IMR1);
	readl(base + IMR1);
}
