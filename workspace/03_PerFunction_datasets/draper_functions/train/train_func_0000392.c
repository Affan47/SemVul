ixgbe_free_fcoe_ddp_resources(struct ixgbe_adapter *adapter)
{
	struct ixgbe_fcoe *fcoe = &adapter->fcoe;
	int cpu, i, ddp_max;


	if (!fcoe->ddp_pool)
		return;

	ddp_max = IXGBE_FCOE_DDP_MAX;

	if (adapter->hw.mac.type == ixgbe_mac_X550)
		ddp_max = IXGBE_FCOE_DDP_MAX_X550;

	for (i = 0; i < ddp_max; i++)
		ixgbe_fcoe_ddp_put(adapter->netdev, i);

	for_each_possible_cpu(cpu)
		ixgbe_fcoe_dma_pool_free(fcoe, cpu);

	dma_unmap_single(&adapter->pdev->dev,
			 fcoe->extra_ddp_buffer_dma,
			 IXGBE_FCBUFF_MIN,
			 DMA_FROM_DEVICE);
	kfree(fcoe->extra_ddp_buffer);

	fcoe->extra_ddp_buffer = NULL;
	fcoe->extra_ddp_buffer_dma = 0;
}
