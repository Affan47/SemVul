mic_smpt_init(struct mic_device *mdev)
{
	int i, err = 0;
	dma_addr_t dma_addr;
	struct mic_smpt_info *smpt_info;

	mdev->smpt = kmalloc(sizeof(*mdev->smpt), GFP_KERNEL);
	if (!mdev->smpt)
		return -ENOMEM;

	smpt_info = mdev->smpt;
	mdev->smpt_ops->init(mdev);
	smpt_info->entry = kmalloc_array(smpt_info->info.num_reg,
					 sizeof(*smpt_info->entry), GFP_KERNEL);
	if (!smpt_info->entry) {
		err = -ENOMEM;
		goto free_smpt;
	}
	spin_lock_init(&smpt_info->smpt_lock);
	for (i = 0; i < smpt_info->info.num_reg; i++) {
		dma_addr = i * smpt_info->info.page_size;
		smpt_info->entry[i].dma_addr = dma_addr;
		smpt_info->entry[i].ref_count = 0;
		mdev->smpt_ops->set(mdev, dma_addr, i);
	}
	smpt_info->ref_count = 0;
	smpt_info->map_count = 0;
	smpt_info->unmap_count = 0;
	return 0;
free_smpt:
	kfree(smpt_info);
	return err;
}
