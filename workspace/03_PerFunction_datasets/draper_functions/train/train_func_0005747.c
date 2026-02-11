set_carrier(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;
	u8 speed;

	speed = rtl8152_get_speed(tp);

	if (speed & LINK_STATUS) {
		if (!netif_carrier_ok(netdev)) {
			tp->rtl_ops.enable(tp);
			set_bit(RTL8152_SET_RX_MODE, &tp->flags);
			netif_stop_queue(netdev);
			napi_disable(&tp->napi);
			netif_carrier_on(netdev);
			rtl_start_rx(tp);
			napi_enable(&tp->napi);
			netif_wake_queue(netdev);
			netif_info(tp, link, netdev, "carrier on\n");
		} else if (netif_queue_stopped(netdev) &&
			   skb_queue_len(&tp->tx_queue) < tp->tx_qlen) {
			netif_wake_queue(netdev);
		}
	} else {
		if (netif_carrier_ok(netdev)) {
			netif_carrier_off(netdev);
			napi_disable(&tp->napi);
			tp->rtl_ops.disable(tp);
			napi_enable(&tp->napi);
			netif_info(tp, link, netdev, "carrier off\n");
		}
	}
}
