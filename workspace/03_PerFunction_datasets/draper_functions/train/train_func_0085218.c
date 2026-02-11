start_transfer(struct sl811 *sl811)
{
	if (sl811->port1 & USB_PORT_STAT_SUSPEND)
		return;
	if (sl811->active_a == NULL) {
		sl811->active_a = start(sl811, SL811_EP_A(SL811_HOST_BUF));
		if (sl811->active_a != NULL)
			sl811->jiffies_a = jiffies + MIN_JIFFIES;
	}
#ifdef USE_B
	if (sl811->active_b == NULL) {
		sl811->active_b = start(sl811, SL811_EP_B(SL811_HOST_BUF));
		if (sl811->active_b != NULL)
			sl811->jiffies_b = jiffies + MIN_JIFFIES;
	}
#endif
}
