stop_ap_mode(struct adapter *padapter)
{
	struct list_head *phead, *plist;
	struct rtw_wlan_acl_node *paclnode;
	struct sta_info *psta = NULL;
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct wlan_acl_pool *pacl_list = &pstapriv->acl_list;
	struct __queue *pacl_node_q = &pacl_list->acl_node_q;

	pmlmepriv->update_bcn = false;
	pmlmeext->bstart_bss = false;


	memset((unsigned char *)&padapter->securitypriv, 0, sizeof(struct security_priv));
	padapter->securitypriv.ndisauthtype = Ndis802_11AuthModeOpen;
	padapter->securitypriv.ndisencryptstatus = Ndis802_11WEPDisabled;


	spin_lock_bh(&(pacl_node_q->lock));
	phead = get_list_head(pacl_node_q);
	plist = phead->next;
	while (phead != plist) {
		paclnode = container_of(plist, struct rtw_wlan_acl_node, list);
		plist = plist->next;

		if (paclnode->valid) {
			paclnode->valid = false;

			list_del_init(&paclnode->list);

			pacl_list->num--;
		}
	}
	spin_unlock_bh(&(pacl_node_q->lock));

	DBG_88E("%s, free acl_node_queue, num =%d\n", __func__, pacl_list->num);

	rtw_sta_flush(padapter);


	rtw_free_all_stainfo(padapter);

	psta = rtw_get_bcmc_stainfo(padapter);
	spin_lock_bh(&(pstapriv->sta_hash_lock));
	rtw_free_stainfo(padapter, psta);
	spin_unlock_bh(&(pstapriv->sta_hash_lock));

	rtw_init_bcmc_stainfo(padapter);

	rtw_free_mlme_priv_ie_data(pmlmepriv);
}
