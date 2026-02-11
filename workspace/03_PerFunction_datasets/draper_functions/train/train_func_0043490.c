r8712_xmitframe_complete(struct _adapter *padapter,
			     struct xmit_priv *pxmitpriv,
			     struct xmit_buf *pxmitbuf)
{
	struct hw_xmit *phwxmits;
	sint hwentry;
	struct xmit_frame *pxmitframe = NULL;
#ifdef CONFIG_R8712_TX_AGGR
	struct xmit_frame *p2ndxmitframe = NULL;
#else
	int res = _SUCCESS, xcnt = 0;
#endif

	phwxmits = pxmitpriv->hwxmits;
	hwentry = pxmitpriv->hwxmit_entry;
	if (pxmitbuf == NULL) {
		pxmitbuf = r8712_alloc_xmitbuf(pxmitpriv);
		if (!pxmitbuf)
			return false;
#ifdef CONFIG_R8712_TX_AGGR
		pxmitbuf->aggr_nr = 0;
#endif
	}

	pxmitframe = dequeue_xframe_ex(pxmitpriv, phwxmits, hwentry);

	if (pxmitframe != NULL) {

#ifdef CONFIG_R8712_TX_AGGR


		if (AGGR_NR_HIGH_BOUND > 1)
			p2ndxmitframe = dequeue_xframe_ex(pxmitpriv, phwxmits,
							hwentry);
		if (pxmitframe->frame_tag != DATA_FRAMETAG) {
			r8712_free_xmitbuf(pxmitpriv, pxmitbuf);
			return false;
		}
		if (p2ndxmitframe != NULL)
			if (p2ndxmitframe->frame_tag != DATA_FRAMETAG) {
				r8712_free_xmitbuf(pxmitpriv, pxmitbuf);
				return false;
			}
		r8712_xmitframe_aggr_1st(pxmitbuf, pxmitframe);
		if (p2ndxmitframe != NULL) {
			u16 total_length;

			total_length = r8712_xmitframe_aggr_next(
				pxmitbuf, p2ndxmitframe);
			do {
				p2ndxmitframe = dequeue_xframe_ex(
					pxmitpriv, phwxmits, hwentry);
				if (p2ndxmitframe != NULL)
					total_length =
						r8712_xmitframe_aggr_next(
							pxmitbuf,
							p2ndxmitframe);
				else
					break;
			} while (total_length <= 0x1800 &&
				pxmitbuf->aggr_nr <= AGGR_NR_HIGH_BOUND);
		}
		if (pxmitbuf->aggr_nr > 0)
			r8712_dump_aggr_xframe(pxmitbuf, pxmitframe);

#else

		xmitframe_xmitbuf_attach(pxmitframe, pxmitbuf);
		if (pxmitframe->frame_tag == DATA_FRAMETAG) {
			if (pxmitframe->attrib.priority <= 15)
				res = r8712_xmitframe_coalesce(padapter,
					pxmitframe->pkt, pxmitframe);


			r8712_xmit_complete(padapter, pxmitframe);
		}
		if (res == _SUCCESS)
			dump_xframe(padapter, pxmitframe);
		else
			r8712_free_xmitframe_ex(pxmitpriv, pxmitframe);
		xcnt++;
#endif

	} else {
		r8712_free_xmitbuf(pxmitpriv, pxmitbuf);
		return false;
	}
	return true;
}
