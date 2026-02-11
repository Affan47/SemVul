r8712_free_xmitbuf(struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf)
{
	unsigned long irqL;
	struct  __queue *pfree_xmitbuf_queue = &pxmitpriv->free_xmitbuf_queue;

	if (pxmitbuf == NULL)
		return _FAIL;
	spin_lock_irqsave(&pfree_xmitbuf_queue->lock, irqL);
	list_del_init(&pxmitbuf->list);
	list_add_tail(&(pxmitbuf->list), &pfree_xmitbuf_queue->queue);
	pxmitpriv->free_xmitbuf_cnt++;
	spin_unlock_irqrestore(&pfree_xmitbuf_queue->lock, irqL);
	return _SUCCESS;
}
