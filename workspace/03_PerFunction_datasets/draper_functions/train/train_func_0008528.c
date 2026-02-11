draw_led(NetMon *net, int rxtx, int led_index)
	{
	GkrellmPanel	*p;
	GkrellmDecal	*led;

	if (!net->chart)
		return;
	p = net->chart->panel;
	if (rxtx == RX_LED)
		led = net->rxled;
	else
		led = net->txled;

	gkrellm_draw_decal_pixmap(p, led, led_index);
	}
