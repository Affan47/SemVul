megasas_create_frame_pool(struct megasas_instance *instance)
{
	int i;
	u32 max_cmd;
	u32 sge_sz;
	u32 total_sz;
	u32 frame_count;
	struct megasas_cmd *cmd;

	max_cmd = instance->max_mfi_cmds;


	sge_sz = (IS_DMA64) ? sizeof(struct megasas_sge64) :
	    sizeof(struct megasas_sge32);

	if (instance->flag_ieee)
		sge_sz = sizeof(struct megasas_sge_skinny);


	frame_count = instance->ctrl_context ? (3 + 1) : (15 + 1);
	total_sz = MEGAMFI_FRAME_SIZE * frame_count;


	instance->frame_dma_pool = pci_pool_create("megasas frame pool",
					instance->pdev, total_sz, 256, 0);

	if (!instance->frame_dma_pool) {
		dev_printk(KERN_DEBUG, &instance->pdev->dev, "failed to setup frame pool\n");
		return -ENOMEM;
	}

	instance->sense_dma_pool = pci_pool_create("megasas sense pool",
						   instance->pdev, 128, 4, 0);

	if (!instance->sense_dma_pool) {
		dev_printk(KERN_DEBUG, &instance->pdev->dev, "failed to setup sense pool\n");

		pci_pool_destroy(instance->frame_dma_pool);
		instance->frame_dma_pool = NULL;

		return -ENOMEM;
	}


	for (i = 0; i < max_cmd; i++) {

		cmd = instance->cmd_list[i];

		cmd->frame = pci_pool_alloc(instance->frame_dma_pool,
					    GFP_KERNEL, &cmd->frame_phys_addr);

		cmd->sense = pci_pool_alloc(instance->sense_dma_pool,
					    GFP_KERNEL, &cmd->sense_phys_addr);


		if (!cmd->frame || !cmd->sense) {
			dev_printk(KERN_DEBUG, &instance->pdev->dev, "pci_pool_alloc failed\n");
			megasas_teardown_frame_pool(instance);
			return -ENOMEM;
		}

		memset(cmd->frame, 0, total_sz);
		cmd->frame->io.context = cpu_to_le32(cmd->index);
		cmd->frame->io.pad_0 = 0;
		if (!instance->ctrl_context && reset_devices)
			cmd->frame->hdr.cmd = MFI_CMD_INVALID;
	}

	return 0;
}
