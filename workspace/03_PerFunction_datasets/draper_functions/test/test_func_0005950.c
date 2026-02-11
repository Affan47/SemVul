i40e_diag_test(struct net_device *netdev,
			   struct ethtool_test *eth_test, u64 *data)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	bool if_running = netif_running(netdev);
	struct i40e_pf *pf = np->vsi->back;

	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {

		netif_info(pf, drv, netdev, "offline testing starting\n");

		set_bit(__I40E_TESTING, &pf->state);

		if (i40e_active_vfs(pf) || i40e_active_vmdqs(pf)) {
			dev_warn(&pf->pdev->dev,
				 "Please take active VFs and Netqueues offline and restart the adapter before running NIC diagnostics\n");
			data[I40E_ETH_TEST_REG]		= 1;
			data[I40E_ETH_TEST_EEPROM]	= 1;
			data[I40E_ETH_TEST_INTR]	= 1;
			data[I40E_ETH_TEST_LOOPBACK]	= 1;
			data[I40E_ETH_TEST_LINK]	= 1;
			eth_test->flags |= ETH_TEST_FL_FAILED;
			clear_bit(__I40E_TESTING, &pf->state);
			goto skip_ol_tests;
		}


		if (if_running)

			dev_close(netdev);
		else


			i40e_do_reset(pf, BIT(__I40E_PF_RESET_REQUESTED));

		if (i40e_link_test(netdev, &data[I40E_ETH_TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (i40e_eeprom_test(netdev, &data[I40E_ETH_TEST_EEPROM]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (i40e_intr_test(netdev, &data[I40E_ETH_TEST_INTR]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (i40e_loopback_test(netdev, &data[I40E_ETH_TEST_LOOPBACK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;


		if (i40e_reg_test(netdev, &data[I40E_ETH_TEST_REG]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		clear_bit(__I40E_TESTING, &pf->state);
		i40e_do_reset(pf, BIT(__I40E_PF_RESET_REQUESTED));

		if (if_running)
			dev_open(netdev);
	} else {

		netif_info(pf, drv, netdev, "online testing starting\n");

		if (i40e_link_test(netdev, &data[I40E_ETH_TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;


		data[I40E_ETH_TEST_REG] = 0;
		data[I40E_ETH_TEST_EEPROM] = 0;
		data[I40E_ETH_TEST_INTR] = 0;
		data[I40E_ETH_TEST_LOOPBACK] = 0;
	}

skip_ol_tests:

	netif_info(pf, drv, netdev, "testing finished\n");
}
