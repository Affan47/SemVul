pre_xmitframe(struct adapter *adapt, struct xmit_frame *pxmitframe)
{
	s32 res;
	struct xmit_buf *pxmitbuf = NULL;
	struct xmit_priv *pxmitpriv = &adapt->xmitpriv;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;
	struct mlme_priv *pmlmepriv = &adapt->mlmepriv;

	spin_lock_bh(&pxmitpriv->lock);

	if (rtw_txframes_sta_ac_pending(adapt, pattrib) > 0)
		goto enqueue;

	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY|_FW_UNDER_LINKING) == true)
		goto enqueue;

	pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
	if (!pxmitbuf)
		goto enqueue;

	spin_unlock_bh(&pxmitpriv->lock);

	pxmitframe->pxmitbuf = pxmitbuf;
	pxmitframe->buf_addr = pxmitbuf->pbuf;
	pxmitbuf->priv_data = pxmitframe;

	if (xmitframe_direct(adapt, pxmitframe) != _SUCCESS) {
		rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
		rtw_free_xmitframe(pxmitpriv, pxmitframe);
	}

	return true;

enqueue:
	res = rtw_xmitframe_enqueue(adapt, pxmitframe);
	spin_unlock_bh(&pxmitpriv->lock);

	if (res != _SUCCESS) {
		RT_TRACE(_module_xmit_osdep_c_, _drv_err_, ("pre_xmitframe: enqueue xmitframe fail\n"));
		rtw_free_xmitframe(pxmitpriv, pxmitframe);


		pxmitpriv->tx_pkts--;
		pxmitpriv->tx_drop++;
		return true;
	}

	return false;
}
