lanai_send(struct atm_vcc *atmvcc, struct sk_buff *skb)
{
	struct lanai_vcc *lvcc = (struct lanai_vcc *) atmvcc->dev_data;
	struct lanai_dev *lanai = (struct lanai_dev *) atmvcc->dev->dev_data;
	unsigned long flags;
	if (unlikely(lvcc == NULL || lvcc->vbase == NULL ||
	      lvcc->tx.atmvcc != atmvcc))
		goto einval;
#ifdef DEBUG
	if (unlikely(skb == NULL)) {
		DPRINTK("lanai_send: skb==NULL for vci=%d\n", atmvcc->vci);
		goto einval;
	}
	if (unlikely(lanai == NULL)) {
		DPRINTK("lanai_send: lanai==NULL for vci=%d\n", atmvcc->vci);
		goto einval;
	}
#endif
	ATM_SKB(skb)->vcc = atmvcc;
	switch (atmvcc->qos.aal) {
		case ATM_AAL5:
			read_lock_irqsave(&vcc_sklist_lock, flags);
			vcc_tx_aal5(lanai, lvcc, skb);
			read_unlock_irqrestore(&vcc_sklist_lock, flags);
			return 0;
		case ATM_AAL0:
			if (unlikely(skb->len != ATM_CELL_SIZE-1))
				goto einval;

			cpu_to_be32s((u32 *) skb->data);
			read_lock_irqsave(&vcc_sklist_lock, flags);
			vcc_tx_aal0(lanai, lvcc, skb);
			read_unlock_irqrestore(&vcc_sklist_lock, flags);
			return 0;
	}
	DPRINTK("lanai_send: bad aal=%d on vci=%d\n", (int) atmvcc->qos.aal,
	    atmvcc->vci);
    einval:
	lanai_free_skb(atmvcc, skb);
	return -EINVAL;
}
