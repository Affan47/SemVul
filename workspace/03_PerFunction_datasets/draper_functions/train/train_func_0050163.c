twa_free_device_extension(TW_Device_Extension *tw_dev)
{
	if (tw_dev->command_packet_virt[0])
		pci_free_consistent(tw_dev->tw_pci_dev,
				    sizeof(TW_Command_Full)*TW_Q_LENGTH,
				    tw_dev->command_packet_virt[0],
				    tw_dev->command_packet_phys[0]);

	if (tw_dev->generic_buffer_virt[0])
		pci_free_consistent(tw_dev->tw_pci_dev,
				    TW_SECTOR_SIZE*TW_Q_LENGTH,
				    tw_dev->generic_buffer_virt[0],
				    tw_dev->generic_buffer_phys[0]);

	kfree(tw_dev->event_queue[0]);
}
