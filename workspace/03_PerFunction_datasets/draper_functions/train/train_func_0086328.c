ar5523_disconnect(struct usb_interface *intf)
{
	struct ieee80211_hw *hw = usb_get_intfdata(intf);
	struct ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "detaching\n");
	set_bit(AR5523_USB_DISCONNECTED, &ar->flags);

	ieee80211_unregister_hw(hw);

	ar5523_cancel_rx_cmd(ar);
	ar5523_free_tx_cmd(ar);
	ar5523_free_rx_cmd(ar);
	ar5523_free_rx_bufs(ar);

	destroy_workqueue(ar->wq);

	ieee80211_free_hw(hw);
	usb_set_intfdata(intf, NULL);
}
