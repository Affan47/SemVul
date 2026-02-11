hp100_hwinit(struct net_device *dev)
{
	int ioaddr = dev->base_addr;
	struct hp100_private *lp = netdev_priv(dev);

#ifdef HP100_DEBUG_B
	hp100_outw(0x4202, TRACE);
	printk("hp100: %s: hwinit\n", dev->name);
#endif


	hp100_page(PERFORMANCE);
	hp100_outw(0xfefe, IRQ_MASK);
	hp100_outw(0xffff, IRQ_STATUS);

	hp100_outw(HP100_INT_EN | HP100_RESET_LB, OPTION_LSW);
	hp100_outw(HP100_TRI_INT | HP100_SET_HB, OPTION_LSW);

	if (lp->mode == 1) {
		hp100_BM_shutdown(dev);
		wait();
	} else {
		hp100_outw(HP100_INT_EN | HP100_RESET_LB, OPTION_LSW);
		hp100_cascade_reset(dev, 1);
		hp100_page(MAC_CTRL);
		hp100_andb(~(HP100_RX_EN | HP100_TX_EN), MAC_CFG_1);
	}


	hp100_load_eeprom(dev, 0);

	wait();


	hp100_cascade_reset(dev, 1);


	hp100_outw(HP100_DEBUG_EN |
		   HP100_RX_HDR |
		   HP100_EE_EN |
		   HP100_BM_WRITE |
		   HP100_BM_READ | HP100_RESET_HB |
		   HP100_FAKE_INT |
		   HP100_INT_EN |
		   HP100_MEM_EN |
		   HP100_IO_EN | HP100_RESET_LB, OPTION_LSW);

	hp100_outw(HP100_TRI_INT |
		   HP100_MMAP_DIS | HP100_SET_HB, OPTION_LSW);

	hp100_outb(HP100_PRIORITY_TX |
		   HP100_ADV_NXT_PKT |
		   HP100_TX_CMD | HP100_RESET_LB, OPTION_MSW);


	hp100_mmuinit(dev);


	wait();


	hp100_cascade_reset(dev, 0);


	if ((lp->lan_type == HP100_LAN_100) || (lp->lan_type == HP100_LAN_ERR))
		hp100_login_to_vg_hub(dev, 0);

}
