snpnet_close ( struct net_device *netdev ) {
	struct snpnet_device *snpnetdev = netdev->priv;
	EFI_SIMPLE_NETWORK_PROTOCOL *snp = snpnetdev->snp;
	EFI_STATUS efirc;
	int rc;

	if ( snpnetdev->close_state != EfiSimpleNetworkInitialized ) {
		if ( ( efirc = snp->Shutdown ( snp ) ) != 0 ) {
			rc = -EEFI ( efirc );
			DBGC ( snp, "SNP %p could not shut down: %s\n",
			       snp, strerror ( rc ) );
		}
	}
}
