qh_append_tds(struct oxu_hcd *oxu,
				struct urb *urb, struct list_head *qtd_list,
				int epnum, void	**ptr)
{
	struct ehci_qh *qh = NULL;

	qh = (struct ehci_qh *) *ptr;
	if (unlikely(qh == NULL)) {

		qh = qh_make(oxu, urb, GFP_ATOMIC);
		*ptr = qh;
	}
	if (likely(qh != NULL)) {
		struct ehci_qtd	*qtd;

		if (unlikely(list_empty(qtd_list)))
			qtd = NULL;
		else
			qtd = list_entry(qtd_list->next, struct ehci_qtd,
					qtd_list);


		if (unlikely(epnum == 0)) {


			if (usb_pipedevice(urb->pipe) == 0)
				qh->hw_info1 &= ~QH_ADDR_MASK;
		}


		if (likely(qtd != NULL)) {
			struct ehci_qtd	*dummy;
			dma_addr_t dma;
			__le32 token;


			token = qtd->hw_token;
			qtd->hw_token = HALT_BIT;
			wmb();
			dummy = qh->dummy;

			dma = dummy->qtd_dma;
			*dummy = *qtd;
			dummy->qtd_dma = dma;

			list_del(&qtd->qtd_list);
			list_add(&dummy->qtd_list, qtd_list);
			list_splice(qtd_list, qh->qtd_list.prev);

			ehci_qtd_init(qtd, qtd->qtd_dma);
			qh->dummy = qtd;


			dma = qtd->qtd_dma;
			qtd = list_entry(qh->qtd_list.prev,
					struct ehci_qtd, qtd_list);
			qtd->hw_next = QTD_NEXT(dma);


			dummy->hw_token = (token & ~(0x80));
			wmb();
			dummy->hw_token = token;

			urb->hcpriv = qh_get(qh);
		}
	}
	return qh;
}
