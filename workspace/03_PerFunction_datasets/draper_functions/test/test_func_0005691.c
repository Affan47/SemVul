deinit_irq(struct net_device *dev)
{
	perInterface_wlan_t *nic;
	struct wilc *wilc;

	nic = netdev_priv(dev);
	wilc = nic->wilc;

#if (defined WILC_SPI) || (defined WILC_SDIO_IRQ_GPIO)

	if (&wilc->dev_irq_num != 0) {
		free_irq(wilc->dev_irq_num, wilc);

		gpio_free(GPIO_NUM);
	}
#endif
}
