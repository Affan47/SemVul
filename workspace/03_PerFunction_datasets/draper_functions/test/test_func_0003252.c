wl1251_sdio_interrupt(struct sdio_func *func)
{
	struct wl1251 *wl = sdio_get_drvdata(func);

	wl1251_debug(DEBUG_IRQ, "IRQ");


	ieee80211_queue_work(wl->hw, &wl->irq_work);
}
