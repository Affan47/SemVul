rtl8723au_xmitframe_complete(struct rtw_adapter *padapter,
				  struct xmit_priv *pxmitpriv,
				  struct xmit_buf *pxmitbuf)
{
	struct hw_xmit *phwxmits;
	struct xmit_frame *pxmitframe;
	int hwentry;
	int res = _SUCCESS, xcnt = 0;

	phwxmits = pxmitpriv->hwxmits;
	hwentry = pxmitpriv->hwxmit_entry;

	RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, "xmitframe_complete()\n");

	if (pxmitbuf == NULL) {
		pxmitbuf = rtw_alloc_xmitbuf23a(pxmitpriv);
		if (!pxmitbuf)
			return false;
	}
	pxmitframe =  rtw_dequeue_xframe23a(pxmitpriv, phwxmits, hwentry);

	if (pxmitframe) {
		pxmitframe->pxmitbuf = pxmitbuf;

		pxmitframe->buf_addr = pxmitbuf->pbuf;

		pxmitbuf->priv_data = pxmitframe;

		if (pxmitframe->frame_tag == DATA_FRAMETAG) {
			if (pxmitframe->attrib.priority <= 15)
				res = rtw_xmitframe_coalesce23a(padapter, pxmitframe->pkt, pxmitframe);

			rtw_os_xmit_complete23a(padapter, pxmitframe);
		}

		RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_,
			 "xmitframe_complete(): rtw_dump_xframe\n");

		if (res == _SUCCESS) {
			rtw_dump_xframe(padapter, pxmitframe);
		} else {
			rtw_free_xmitbuf23a(pxmitpriv, pxmitbuf);
			rtw_free_xmitframe23a(pxmitpriv, pxmitframe);
		}
		xcnt++;
	} else {
		rtw_free_xmitbuf23a(pxmitpriv, pxmitbuf);
		return false;
	}
	return true;
}
