free_netsgbuf_with_resp(void *buf)
{
	struct octeon_soft_command *sc;
	struct octnet_buf_free_info *finfo;
	struct sk_buff *skb;
	struct lio *lio;
	struct octnic_gather *g;
	int i, frags;

	sc = (struct octeon_soft_command *)buf;
	skb = (struct sk_buff *)sc->callback_arg;
	finfo = (struct octnet_buf_free_info *)&skb->cb;

	lio = finfo->lio;
	g = finfo->g;
	frags = skb_shinfo(skb)->nr_frags;

	dma_unmap_single(&lio->oct_dev->pci_dev->dev,
			 g->sg[0].ptr[0], (skb->len - skb->data_len),
			 DMA_TO_DEVICE);

	i = 1;
	while (frags--) {
		struct skb_frag_struct *frag = &skb_shinfo(skb)->frags[i - 1];

		pci_unmap_page((lio->oct_dev)->pci_dev,
			       g->sg[(i >> 2)].ptr[(i & 3)],
			       frag->size, DMA_TO_DEVICE);
		i++;
	}

	dma_unmap_single(&lio->oct_dev->pci_dev->dev,
			 finfo->dptr, g->sg_size,
			 DMA_TO_DEVICE);

	spin_lock(&lio->lock);
	list_add_tail(&g->list, &lio->glist);
	spin_unlock(&lio->lock);


	check_txq_state(lio, skb);
}
