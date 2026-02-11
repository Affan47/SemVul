rx_bottom(rxdrv_t *rx)
{
	rx_check(rx);
	g_assert(rx->upper == NULL);

	return rx_deep_bottom(rx);
}
