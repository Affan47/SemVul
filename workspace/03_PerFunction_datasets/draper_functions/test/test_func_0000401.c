phantom_probe ( struct pci_device *pci ) {
	struct net_device *netdev;
	struct phantom_nic *phantom;
	struct settings *parent_settings;
	int rc;


	netdev = alloc_etherdev ( sizeof ( *phantom ) );
	if ( ! netdev ) {
		rc = -ENOMEM;
		goto err_alloc_etherdev;
	}
	netdev_init ( netdev, &phantom_operations );
	phantom = netdev_priv ( netdev );
	pci_set_drvdata ( pci, netdev );
	netdev->dev = &pci->dev;
	memset ( phantom, 0, sizeof ( *phantom ) );
	phantom->port = PCI_FUNC ( pci->busdevfn );
	assert ( phantom->port < PHN_MAX_NUM_PORTS );
	settings_init ( &phantom->settings,
			&phantom_settings_operations,
			&netdev->refcnt, PHN_CLP_TAG_MAGIC );


	adjust_pci_device ( pci );


	if ( ( rc = phantom_map_crb ( phantom, pci ) ) != 0 )
		goto err_map_crb;


	if ( PCI_FUNC ( pci->busdevfn ) == 0 ) {
		unsigned int i;
		for ( i = 0 ; i < 8 ; i++ ) {
			uint32_t temp;
			pci->busdevfn =
				PCI_BUSDEVFN ( PCI_BUS ( pci->busdevfn ),
					       PCI_SLOT ( pci->busdevfn ), i );
			pci_read_config_dword ( pci, 0xc8, &temp );
			pci_read_config_dword ( pci, 0xc8, &temp );
			pci_write_config_dword ( pci, 0xc8, 0xf1000 );
		}
		pci->busdevfn = PCI_BUSDEVFN ( PCI_BUS ( pci->busdevfn ),
					       PCI_SLOT ( pci->busdevfn ), 0 );
	}


	if ( ( rc = phantom_init_cmdpeg ( phantom ) ) != 0 )
		goto err_init_cmdpeg;


	if ( ( rc = phantom_init_rcvpeg ( phantom ) ) != 0 )
		goto err_init_rcvpeg;


	phantom_get_macaddr ( phantom, netdev->hw_addr );


	if ( ( rc = phantom_check_boot_enable ( phantom ) ) != 0 )
		goto err_check_boot_enable;


	if ( ( rc = register_netdev ( netdev ) ) != 0 ) {
		DBGC ( phantom, "Phantom %p could not register net device: "
		       "%s\n", phantom, strerror ( rc ) );
		goto err_register_netdev;
	}


	parent_settings = netdev_settings ( netdev );
	if ( ( rc = register_settings ( &phantom->settings,
					parent_settings, "clp" ) ) != 0 ) {
		DBGC ( phantom, "Phantom %p could not register settings: "
		       "%s\n", phantom, strerror ( rc ) );
		goto err_register_settings;
	}

	return 0;

	unregister_settings ( &phantom->settings );
 err_register_settings:
	unregister_netdev ( netdev );
 err_register_netdev:
 err_check_boot_enable:
 err_init_rcvpeg:
 err_init_cmdpeg:
 err_map_crb:
	netdev_nullify ( netdev );
	netdev_put ( netdev );
 err_alloc_etherdev:
	return rc;
}
