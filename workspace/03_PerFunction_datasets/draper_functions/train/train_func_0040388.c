init_irq(struct net_device *dev)
{
	int ret = 0;
	perInterface_wlan_t *nic;
	struct wilc *wl;

	nic = netdev_priv(dev);
	wl = nic->wilc;


	if ((gpio_request(GPIO_NUM, "WILC_INTR") == 0) &&
	    (gpio_direction_input(GPIO_NUM) == 0)) {
#if defined(CUSTOMER_PLATFORM)


#else
		wl->dev_irq_num = gpio_to_irq(GPIO_NUM);
#endif
	} else {
		ret = -1;
		PRINT_ER("could not obtain gpio for WILC_INTR\n");
	}

	if ((ret != -1) && (request_threaded_irq(wl->dev_irq_num, isr_uh_routine, isr_bh_routine,
						  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						  "WILC_IRQ", dev)) < 0) {

		PRINT_ER("Failed to request IRQ for GPIO: %d\n", GPIO_NUM);
		ret = -1;
	} else {

		PRINT_D(INIT_DBG, "IRQ request succeeded IRQ-NUM= %d on GPIO: %d\n",
			wl->dev_irq_num, GPIO_NUM);
	}

	return ret;
}
