skd_free_skmsg(struct skd_device *skdev)
{
	u32 i;

	if (skdev->skmsg_table == NULL)
		return;

	for (i = 0; i < skdev->num_fitmsg_context; i++) {
		struct skd_fitmsg_context *skmsg;

		skmsg = &skdev->skmsg_table[i];

		if (skmsg->msg_buf != NULL) {
			skmsg->msg_buf += skmsg->offset;
			skmsg->mb_dma_address += skmsg->offset;
			pci_free_consistent(skdev->pdev, SKD_N_FITMSG_BYTES,
					    skmsg->msg_buf,
					    skmsg->mb_dma_address);
		}
		skmsg->msg_buf = NULL;
		skmsg->mb_dma_address = 0;
	}

	kfree(skdev->skmsg_table);
	skdev->skmsg_table = NULL;
}
