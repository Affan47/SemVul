wl12xx_get_rx_buf_align(struct wl1271 *wl, u32 rx_desc)
{
	if (rx_desc & RX_BUF_UNALIGNED_PAYLOAD)
		return WLCORE_RX_BUF_UNALIGNED;

	return WLCORE_RX_BUF_ALIGNED;
}
