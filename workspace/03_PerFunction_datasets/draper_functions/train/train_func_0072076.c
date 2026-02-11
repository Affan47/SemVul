atl1_suspend(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct atl1_adapter *adapter = netdev_priv(netdev);
	struct atl1_hw *hw = &adapter->hw;
	u32 ctrl = 0;
	u32 wufc = adapter->wol;
	u32 val;
	u16 speed;
	u16 duplex;

	netif_device_detach(netdev);
	if (netif_running(netdev))
		atl1_down(adapter);

	atl1_read_phy_reg(hw, MII_BMSR, (u16 *) & ctrl);
	atl1_read_phy_reg(hw, MII_BMSR, (u16 *) & ctrl);
	val = ctrl & BMSR_LSTATUS;
	if (val)
		wufc &= ~ATLX_WUFC_LNKC;
	if (!wufc)
		goto disable_wol;

	if (val) {
		val = atl1_get_speed_and_duplex(hw, &speed, &duplex);
		if (val) {
			if (netif_msg_ifdown(adapter))
				dev_printk(KERN_DEBUG, &pdev->dev,
					"error getting speed/duplex\n");
			goto disable_wol;
		}

		ctrl = 0;


		if (wufc & ATLX_WUFC_MAG)
			ctrl |= (WOL_MAGIC_EN | WOL_MAGIC_PME_EN);
		iowrite32(ctrl, hw->hw_addr + REG_WOL_CTRL);
		ioread32(hw->hw_addr + REG_WOL_CTRL);


		ctrl = MAC_CTRL_RX_EN;
		ctrl |= ((u32)((speed == SPEED_1000) ? MAC_CTRL_SPEED_1000 :
			MAC_CTRL_SPEED_10_100) << MAC_CTRL_SPEED_SHIFT);
		if (duplex == FULL_DUPLEX)
			ctrl |= MAC_CTRL_DUPLX;
		ctrl |= (((u32)adapter->hw.preamble_len &
			MAC_CTRL_PRMLEN_MASK) << MAC_CTRL_PRMLEN_SHIFT);
		__atlx_vlan_mode(netdev->features, &ctrl);
		if (wufc & ATLX_WUFC_MAG)
			ctrl |= MAC_CTRL_BC_EN;
		iowrite32(ctrl, hw->hw_addr + REG_MAC_CTRL);
		ioread32(hw->hw_addr + REG_MAC_CTRL);


		ctrl = ioread32(hw->hw_addr + REG_PCIE_PHYMISC);
		ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
		iowrite32(ctrl, hw->hw_addr + REG_PCIE_PHYMISC);
		ioread32(hw->hw_addr + REG_PCIE_PHYMISC);
	} else {
		ctrl |= (WOL_LINK_CHG_EN | WOL_LINK_CHG_PME_EN);
		iowrite32(ctrl, hw->hw_addr + REG_WOL_CTRL);
		ioread32(hw->hw_addr + REG_WOL_CTRL);
		iowrite32(0, hw->hw_addr + REG_MAC_CTRL);
		ioread32(hw->hw_addr + REG_MAC_CTRL);
		hw->phy_configured = false;
	}

	return 0;

 disable_wol:
	iowrite32(0, hw->hw_addr + REG_WOL_CTRL);
	ioread32(hw->hw_addr + REG_WOL_CTRL);
	ctrl = ioread32(hw->hw_addr + REG_PCIE_PHYMISC);
	ctrl |= PCIE_PHYMISC_FORCE_RCV_DET;
	iowrite32(ctrl, hw->hw_addr + REG_PCIE_PHYMISC);
	ioread32(hw->hw_addr + REG_PCIE_PHYMISC);
	hw->phy_configured = false;

	return 0;
}
