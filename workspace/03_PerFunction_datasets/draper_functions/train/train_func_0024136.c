arbel_remove ( struct pci_device *pci ) {
	struct arbel *arbel = pci_get_drvdata ( pci );
	int i;

	for ( i = ( ARBEL_NUM_PORTS - 1 ) ; i >= 0 ; i-- )
		unregister_ibdev ( arbel->ibdev[i] );
	arbel_destroy_eq ( arbel );
	arbel_cmd_close_hca ( arbel );
	arbel_free_icm ( arbel );
	arbel_stop_firmware ( arbel );
	arbel_stop_firmware ( arbel );
	free_dma ( arbel->mailbox_out, ARBEL_MBOX_SIZE );
	free_dma ( arbel->mailbox_in, ARBEL_MBOX_SIZE );
	for ( i = ( ARBEL_NUM_PORTS - 1 ) ; i >= 0 ; i-- )
		ibdev_put ( arbel->ibdev[i] );
	free ( arbel );
}
