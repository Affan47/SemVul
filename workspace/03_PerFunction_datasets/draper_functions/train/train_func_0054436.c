_rtw_free_network(struct mlme_priv *pmlmepriv, struct wlan_network *pnetwork, u8 isfreeall)
{
	u32 curr_time, delta_time;
	u32 lifetime = SCANQUEUE_LIFETIME;
	struct __queue *free_queue = &(pmlmepriv->free_bss_pool);

	if (pnetwork == NULL)
		return;

	if (pnetwork->fixed)
		return;
	curr_time = jiffies;
	if ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)) ||
	    (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)))
		lifetime = 1;
	if (!isfreeall) {
		delta_time = (curr_time - pnetwork->last_scanned)/HZ;
		if (delta_time < lifetime)
			return;
	}
	spin_lock_bh(&free_queue->lock);
	list_del_init(&(pnetwork->list));
	list_add_tail(&(pnetwork->list), &(free_queue->queue));
	pmlmepriv->num_of_scanned--;
	spin_unlock_bh(&free_queue->lock);
}
