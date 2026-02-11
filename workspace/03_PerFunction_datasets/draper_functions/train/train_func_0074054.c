r8712_free_stainfo(struct _adapter *padapter, struct sta_info *psta)
{
	int i;
	unsigned long irqL0;
	struct  __queue *pfree_sta_queue;
	struct recv_reorder_ctrl *preorder_ctrl;
	struct	sta_xmit_priv *pstaxmitpriv;
	struct	xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct	sta_priv *pstapriv = &padapter->stapriv;

	if (psta == NULL)
		return;
	pfree_sta_queue = &pstapriv->free_sta_queue;
	pstaxmitpriv = &psta->sta_xmitpriv;
	spin_lock_irqsave(&(pxmitpriv->vo_pending.lock), irqL0);
	r8712_free_xmitframe_queue(pxmitpriv, &pstaxmitpriv->vo_q.sta_pending);
	list_del_init(&(pstaxmitpriv->vo_q.tx_pending));
	spin_unlock_irqrestore(&(pxmitpriv->vo_pending.lock), irqL0);
	spin_lock_irqsave(&(pxmitpriv->vi_pending.lock), irqL0);
	r8712_free_xmitframe_queue(pxmitpriv, &pstaxmitpriv->vi_q.sta_pending);
	list_del_init(&(pstaxmitpriv->vi_q.tx_pending));
	spin_unlock_irqrestore(&(pxmitpriv->vi_pending.lock), irqL0);
	spin_lock_irqsave(&(pxmitpriv->bk_pending.lock), irqL0);
	r8712_free_xmitframe_queue(pxmitpriv, &pstaxmitpriv->bk_q.sta_pending);
	list_del_init(&(pstaxmitpriv->bk_q.tx_pending));
	spin_unlock_irqrestore(&(pxmitpriv->bk_pending.lock), irqL0);
	spin_lock_irqsave(&(pxmitpriv->be_pending.lock), irqL0);
	r8712_free_xmitframe_queue(pxmitpriv, &pstaxmitpriv->be_q.sta_pending);
	list_del_init(&(pstaxmitpriv->be_q.tx_pending));
	spin_unlock_irqrestore(&(pxmitpriv->be_pending.lock), irqL0);
	list_del_init(&psta->hash_list);
	pstapriv->asoc_sta_count--;

	_r8712_init_sta_xmit_priv(&psta->sta_xmitpriv);
	_r8712_init_sta_recv_priv(&psta->sta_recvpriv);


	for (i = 0; i < 16; i++) {
		preorder_ctrl = &psta->recvreorder_ctrl[i];
		del_timer(&preorder_ctrl->reordering_ctrl_timer);
	}
	spin_lock(&(pfree_sta_queue->lock));

	list_add_tail(&psta->list, &pfree_sta_queue->queue);
	spin_unlock(&(pfree_sta_queue->lock));
}
