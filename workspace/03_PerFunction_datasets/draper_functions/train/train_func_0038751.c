sky2_all_up(struct sky2_hw *hw)
{
	u32 imask = Y2_IS_BASE;
	int i;

	for (i = 0; i < hw->ports; i++) {
		struct net_device *dev = hw->dev[i];
		struct sky2_port *sky2 = netdev_priv(dev);

		if (!netif_running(dev))
			continue;

		sky2_hw_up(sky2);
		sky2_set_multicast(dev);
		imask |= portirq_msk[i];
		netif_wake_queue(dev);
	}

	if (hw->flags & SKY2_HW_IRQ_SETUP) {
		sky2_write32(hw, B0_IMSK, imask);
		sky2_read32(hw, B0_IMSK);
		sky2_read32(hw, B0_Y2_SP_LISR);
		napi_enable(&hw->napi);
	}
}
