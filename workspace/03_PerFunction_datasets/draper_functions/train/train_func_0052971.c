_rtw_free_recv_priv23a (struct recv_priv *precvpriv)
{
	struct rtw_adapter *padapter = precvpriv->adapter;
	struct recv_frame *precvframe;
	struct list_head *plist, *ptmp;

	rtw_free_uc_swdec_pending_queue23a(padapter);

	list_for_each_safe(plist, ptmp, &precvpriv->free_recv_queue.queue) {
		precvframe = container_of(plist, struct recv_frame, list);
		list_del_init(&precvframe->list);
		kfree(precvframe);
	}

	rtl8723au_free_recv_priv(padapter);
}
