qede_alloc_mem_sb(struct qede_dev *edev,
			     struct qed_sb_info *sb_info,
			     u16 sb_id)
{
	struct status_block *sb_virt;
	dma_addr_t sb_phys;
	int rc;

	sb_virt = dma_alloc_coherent(&edev->pdev->dev,
				     sizeof(*sb_virt),
				     &sb_phys, GFP_KERNEL);
	if (!sb_virt) {
		DP_ERR(edev, "Status block allocation failed\n");
		return -ENOMEM;
	}

	rc = edev->ops->common->sb_init(edev->cdev, sb_info,
					sb_virt, sb_phys, sb_id,
					QED_SB_TYPE_L2_QUEUE);
	if (rc) {
		DP_ERR(edev, "Status block initialization failed\n");
		dma_free_coherent(&edev->pdev->dev, sizeof(*sb_virt),
				  sb_virt, sb_phys);
		return rc;
	}

	return 0;
}
