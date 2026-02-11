_rtw_free_network_nolock(struct	mlme_priv *pmlmepriv, struct wlan_network *pnetwork)
{
	struct __queue *free_queue = &(pmlmepriv->free_bss_pool);

	if (pnetwork == NULL)
		return;
	if (pnetwork->fixed)
		return;
	list_del_init(&(pnetwork->list));
	list_add_tail(&(pnetwork->list), get_list_head(free_queue));
	pmlmepriv->num_of_scanned--;
}
