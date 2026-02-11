cas_tx_timeout(struct net_device *dev)
{
	struct cas *cp = netdev_priv(dev);

	netdev_err(dev, "transmit timed out, resetting\n");
	if (!cp->hw_running) {
		netdev_err(dev, "hrm.. hw not running!\n");
		return;
	}

	netdev_err(dev, "MIF_STATE[%08x]\n",
		   readl(cp->regs + REG_MIF_STATE_MACHINE));

	netdev_err(dev, "MAC_STATE[%08x]\n",
		   readl(cp->regs + REG_MAC_STATE_MACHINE));

	netdev_err(dev, "TX_STATE[%08x:%08x:%08x] FIFO[%08x:%08x:%08x] SM1[%08x] SM2[%08x]\n",
		   readl(cp->regs + REG_TX_CFG),
		   readl(cp->regs + REG_MAC_TX_STATUS),
		   readl(cp->regs + REG_MAC_TX_CFG),
		   readl(cp->regs + REG_TX_FIFO_PKT_CNT),
		   readl(cp->regs + REG_TX_FIFO_WRITE_PTR),
		   readl(cp->regs + REG_TX_FIFO_READ_PTR),
		   readl(cp->regs + REG_TX_SM_1),
		   readl(cp->regs + REG_TX_SM_2));

	netdev_err(dev, "RX_STATE[%08x:%08x:%08x]\n",
		   readl(cp->regs + REG_RX_CFG),
		   readl(cp->regs + REG_MAC_RX_STATUS),
		   readl(cp->regs + REG_MAC_RX_CFG));

	netdev_err(dev, "HP_STATE[%08x:%08x:%08x:%08x]\n",
		   readl(cp->regs + REG_HP_STATE_MACHINE),
		   readl(cp->regs + REG_HP_STATUS0),
		   readl(cp->regs + REG_HP_STATUS1),
		   readl(cp->regs + REG_HP_STATUS2));

#if 1
	atomic_inc(&cp->reset_task_pending);
	atomic_inc(&cp->reset_task_pending_all);
	schedule_work(&cp->reset_task);
#else
	atomic_set(&cp->reset_task_pending, CAS_RESET_ALL);
	schedule_work(&cp->reset_task);
#endif
}
