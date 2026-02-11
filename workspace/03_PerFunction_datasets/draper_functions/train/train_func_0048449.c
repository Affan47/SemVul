rtw_recv_indicatepkt23a(struct rtw_adapter *padapter,
			 struct recv_frame *precv_frame)
{
	struct recv_priv *precvpriv;
	struct sk_buff *skb;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	precvpriv = &padapter->recvpriv;

	skb = precv_frame->pkt;
	if (!skb) {
		RT_TRACE(_module_recv_osdep_c_, _drv_err_,
			 "rtw_recv_indicatepkt23a():skb == NULL!!!!\n");
		goto _recv_indicatepkt_drop;
	}

	RT_TRACE(_module_recv_osdep_c_, _drv_info_,
		 "rtw_recv_indicatepkt23a():skb != NULL !!!\n");
	RT_TRACE(_module_recv_osdep_c_, _drv_info_,
		 "rtw_recv_indicatepkt23a():precv_frame->hdr.rx_data =%p\n",
		 precv_frame->pkt->data);
	RT_TRACE(_module_recv_osdep_c_, _drv_info_,
		 "skb->head =%p skb->data =%p skb->tail =%p skb->end =%p skb->len =%d\n",
		 skb->head, skb->data,
		 skb_tail_pointer(skb), skb_end_pointer(skb), skb->len);

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) {
		struct sk_buff *pskb2 = NULL;
		struct sta_info *psta = NULL;
		struct sta_priv *pstapriv = &padapter->stapriv;
		struct rx_pkt_attrib *pattrib = &precv_frame->attrib;
		int bmcast = is_multicast_ether_addr(pattrib->dst);


		if (!ether_addr_equal(pattrib->dst,
				      myid(&padapter->eeprompriv))) {

			if (bmcast) {
				psta = rtw_get_bcmc_stainfo23a(padapter);
				pskb2 = skb_clone(skb, GFP_ATOMIC);
			} else {
				psta = rtw_get_stainfo23a(pstapriv, pattrib->dst);
			}

			if (psta) {
				struct net_device *pnetdev = padapter->pnetdev;


				skb->dev = pnetdev;
				skb_set_queue_mapping(skb, rtw_recv_select_queue23a(skb));

				rtw_xmit23a_entry23a(skb, pnetdev);

				if (bmcast)
					skb = pskb2;
				else
					goto _recv_indicatepkt_end;
			}
		} else {

		}
	}

	skb->ip_summed = CHECKSUM_NONE;
	skb->dev = padapter->pnetdev;
	skb->protocol = eth_type_trans(skb, padapter->pnetdev);

	netif_rx(skb);

_recv_indicatepkt_end:

	precv_frame->pkt = NULL;

	rtw_free_recvframe23a(precv_frame);

	RT_TRACE(_module_recv_osdep_c_, _drv_info_,
		 "rtw_recv_indicatepkt23a :after netif_rx!!!!\n");
	return _SUCCESS;

_recv_indicatepkt_drop:

	 rtw_free_recvframe23a(precv_frame);
	 return _FAIL;
}
