_rtw_init_recv_priv23a(struct recv_priv *precvpriv,
			struct rtw_adapter *padapter)
{
	struct recv_frame *precvframe;
	int i;
	int res = _SUCCESS;

	spin_lock_init(&precvpriv->lock);

	_rtw_init_queue23a(&precvpriv->free_recv_queue);
	_rtw_init_queue23a(&precvpriv->recv_pending_queue);
	_rtw_init_queue23a(&precvpriv->uc_swdec_pending_queue);

	precvpriv->adapter = padapter;

	for (i = 0; i < NR_RECVFRAME ; i++) {
		precvframe = kzalloc(sizeof(struct recv_frame), GFP_KERNEL);
		if (!precvframe)
			break;
		INIT_LIST_HEAD(&precvframe->list);

		list_add_tail(&precvframe->list,
			      &precvpriv->free_recv_queue.queue);

		precvframe->adapter = padapter;
		precvframe++;
	}

	precvpriv->free_recvframe_cnt = i;
	precvpriv->rx_pending_cnt = 1;

	res = rtl8723au_init_recv_priv(padapter);

	setup_timer(&precvpriv->signal_stat_timer, rtw_signal_stat_timer_hdl23a,
		    (unsigned long)padapter);

	precvpriv->signal_stat_sampling_interval = 1000;

	rtw_set_signal_stat_timer(precvpriv);

	return res;
}
