wil_vring_fini_tx(struct wil6210_priv *wil, int id)
{
	struct vring *vring = &wil->vring_tx[id];
	struct vring_tx_data *txdata = &wil->vring_tx_data[id];

	WARN_ON(!mutex_is_locked(&wil->mutex));

	if (!vring->va)
		return;

	wil_dbg_misc(wil, "%s() id=%d\n", __func__, id);

	spin_lock_bh(&txdata->lock);
	txdata->dot1x_open = false;
	txdata->enabled = 0;
	spin_unlock_bh(&txdata->lock);

	if (test_bit(wil_status_napi_en, wil->status))
		napi_synchronize(&wil->napi_tx);

	wil_vring_free(wil, vring, 1);
	memset(txdata, 0, sizeof(*txdata));
}
