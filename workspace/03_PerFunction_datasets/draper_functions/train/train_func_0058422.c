mic_smpt_restore(struct mic_device *mdev)
{
	int i;
	dma_addr_t dma_addr;

	for (i = 0; i < mdev->smpt->info.num_reg; i++) {
		dma_addr = mdev->smpt->entry[i].dma_addr;
		mdev->smpt_ops->set(mdev, dma_addr, i);
	}
}
