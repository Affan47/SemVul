efab_open ( struct net_device *netdev )
{
	struct efab_nic *efab = netdev_priv ( netdev );
	struct efab_rx_queue *rx_queue = &efab->rx_queue;
	int rc;

	rc = falcon_reset ( efab );
	if ( rc )
		goto fail1;

	rc = efab->board_op->init ( efab );
	if ( rc )
		goto fail2;

	rc = falcon_init_sram ( efab );
	if ( rc )
		goto fail3;


	falcon_setup_nic ( efab );

	rc = efab_alloc_resources ( efab );
	if ( rc )
		goto fail4;

	falcon_init_resources ( efab );


	rc = efab_fill_rx_queue ( efab, rx_queue );
	if ( rc )
		goto fail5;


	rc = efab_init_mac ( efab );
	if ( rc )
		goto fail6;

	return 0;

fail6:
fail5:
	efab_free_resources ( efab );
fail4:
fail3:
	efab->board_op->fini ( efab );
fail2:
	falcon_reset ( efab );
fail1:
	return rc;
}
