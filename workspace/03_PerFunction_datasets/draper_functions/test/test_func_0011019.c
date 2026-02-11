mgsl_add_device( struct mgsl_struct *info )
{
	info->next_device = NULL;
	info->line = mgsl_device_count;
	sprintf(info->device_name,"ttySL%d",info->line);

	if (info->line < MAX_TOTAL_DEVICES) {
		if (maxframe[info->line])
			info->max_frame_size = maxframe[info->line];

		if (txdmabufs[info->line]) {
			info->num_tx_dma_buffers = txdmabufs[info->line];
			if (info->num_tx_dma_buffers < 1)
				info->num_tx_dma_buffers = 1;
		}

		if (txholdbufs[info->line]) {
			info->num_tx_holding_buffers = txholdbufs[info->line];
			if (info->num_tx_holding_buffers < 1)
				info->num_tx_holding_buffers = 1;
			else if (info->num_tx_holding_buffers > MAX_TX_HOLDING_BUFFERS)
				info->num_tx_holding_buffers = MAX_TX_HOLDING_BUFFERS;
		}
	}

	mgsl_device_count++;

	if ( !mgsl_device_list )
		mgsl_device_list = info;
	else {
		struct mgsl_struct *current_dev = mgsl_device_list;
		while( current_dev->next_device )
			current_dev = current_dev->next_device;
		current_dev->next_device = info;
	}

	if ( info->max_frame_size < 4096 )
		info->max_frame_size = 4096;
	else if ( info->max_frame_size > 65535 )
		info->max_frame_size = 65535;

	if ( info->bus_type == MGSL_BUS_TYPE_PCI ) {
		printk( "SyncLink PCI v%d %s: IO=%04X IRQ=%d Mem=%08X,%08X MaxFrameSize=%u\n",
			info->hw_version + 1, info->device_name, info->io_base, info->irq_level,
			info->phys_memory_base, info->phys_lcr_base,
		     	info->max_frame_size );
	} else {
		printk( "SyncLink ISA %s: IO=%04X IRQ=%d DMA=%d MaxFrameSize=%u\n",
			info->device_name, info->io_base, info->irq_level, info->dma_level,
		     	info->max_frame_size );
	}

#if SYNCLINK_GENERIC_HDLC
	hdlcdev_init(info);
#endif

}
