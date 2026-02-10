_mic_start(struct cosm_device *cdev, int id)
{
	struct mic_device *mdev = cosmdev_to_mdev(cdev);
	int rc;

	mic_bootparam_init(mdev);
	mdev->dma_mbdev = mbus_register_device(&mdev->pdev->dev,
					       MBUS_DEV_DMA_HOST, &mic_dma_ops,
					       &mbus_hw_ops, id, mdev->mmio.va);
	if (IS_ERR(mdev->dma_mbdev)) {
		rc = PTR_ERR(mdev->dma_mbdev);
		goto unlock_ret;
	}
	if (!mic_request_dma_chans(mdev)) {
		rc = -ENODEV;
		goto dma_remove;
	}
	mdev->scdev = scif_register_device(&mdev->pdev->dev, MIC_SCIF_DEV,
					   &__mic_dma_ops, &scif_hw_ops,
					   id + 1, 0, &mdev->mmio,
					   &mdev->aper, mdev->dp, NULL,
					   mdev->dma_ch, mdev->num_dma_ch,
					   true);
	if (IS_ERR(mdev->scdev)) {
		rc = PTR_ERR(mdev->scdev);
		goto dma_free;
	}

	rc = mdev->ops->load_mic_fw(mdev, NULL);
	if (rc)
		goto scif_remove;
	mic_smpt_restore(mdev);
	mic_intr_restore(mdev);
	mdev->intr_ops->enable_interrupts(mdev);
	mdev->ops->write_spad(mdev, MIC_DPLO_SPAD, mdev->dp_dma_addr);
	mdev->ops->write_spad(mdev, MIC_DPHI_SPAD, mdev->dp_dma_addr >> 32);
	mdev->ops->send_firmware_intr(mdev);
	goto unlock_ret;
scif_remove:
	scif_unregister_device(mdev->scdev);
dma_free:
	mic_free_dma_chans(mdev);
dma_remove:
	mbus_unregister_device(mdev->dma_mbdev);
unlock_ret:
	return rc;
}
