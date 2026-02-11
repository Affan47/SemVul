rtl8152_resume(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);

	mutex_lock(&tp->control);

	if (!test_bit(SELECTIVE_SUSPEND, &tp->flags)) {
		tp->rtl_ops.init(tp);
		netif_device_attach(tp->netdev);
	}

	if (netif_running(tp->netdev) && tp->netdev->flags & IFF_UP) {
		if (test_bit(SELECTIVE_SUSPEND, &tp->flags)) {
			rtl_runtime_suspend_enable(tp, false);
			clear_bit(SELECTIVE_SUSPEND, &tp->flags);
			napi_disable(&tp->napi);
			set_bit(WORK_ENABLE, &tp->flags);

			if (netif_carrier_ok(tp->netdev)) {
				if (rtl8152_get_speed(tp) & LINK_STATUS) {
					rtl_start_rx(tp);
				} else {
					netif_carrier_off(tp->netdev);
					tp->rtl_ops.disable(tp);
					netif_info(tp, link, tp->netdev,
						   "linking down\n");
				}
			}

			napi_enable(&tp->napi);
		} else {
			tp->rtl_ops.up(tp);
			rtl8152_set_speed(tp, AUTONEG_ENABLE,
					  tp->mii.supports_gmii ?
					  SPEED_1000 : SPEED_100,
					  DUPLEX_FULL);
			netif_carrier_off(tp->netdev);
			set_bit(WORK_ENABLE, &tp->flags);
		}
		usb_submit_urb(tp->intr_urb, GFP_KERNEL);
	} else if (test_bit(SELECTIVE_SUSPEND, &tp->flags)) {
		if (tp->netdev->flags & IFF_UP)
			rtl_runtime_suspend_enable(tp, false);
		clear_bit(SELECTIVE_SUSPEND, &tp->flags);
	}

	mutex_unlock(&tp->control);

	return 0;
}
