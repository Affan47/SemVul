sproc_drv_remove(struct platform_device *pdev)
{
	struct ste_modem_device *mdev =
		container_of(pdev, struct ste_modem_device, pdev);
	struct sproc *sproc = mdev->drv_data;

	sproc_dbg(sproc, "remove ste-modem\n");


	sproc->mdev->ops.setup(sproc->mdev, NULL);


	rproc_del(sproc->rproc);
	dma_free_coherent(sproc->rproc->dev.parent, SPROC_FW_SIZE,
			  sproc->fw_addr, sproc->fw_dma_addr);
	rproc_put(sproc->rproc);

	mdev->drv_data = NULL;

	return 0;
}
