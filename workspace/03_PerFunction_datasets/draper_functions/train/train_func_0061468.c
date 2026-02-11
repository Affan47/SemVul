wil_back_tx_flush(struct wil6210_priv *wil)
{
	struct wil_back_tx *evt, *t;

	wil_dbg_misc(wil, "%s()\n", __func__);

	mutex_lock(&wil->back_tx_mutex);

	list_for_each_entry_safe(evt, t, &wil->back_tx_pending, list) {
		list_del(&evt->list);
		kfree(evt);
	}

	mutex_unlock(&wil->back_tx_mutex);
}
