get_scq(ns_dev *card, int size, u32 scd)
{
	scq_info *scq;
	int i;

	if (size != VBR_SCQSIZE && size != CBR_SCQSIZE)
		return NULL;

	scq = kmalloc(sizeof(scq_info), GFP_KERNEL);
	if (!scq)
		return NULL;
        scq->org = dma_alloc_coherent(&card->pcidev->dev,
				      2 * size,  &scq->dma, GFP_KERNEL);
	if (!scq->org) {
		kfree(scq);
		return NULL;
	}
	scq->skb = kmalloc(sizeof(struct sk_buff *) *
			   (size / NS_SCQE_SIZE), GFP_KERNEL);
	if (!scq->skb) {
		kfree(scq->org);
		kfree(scq);
		return NULL;
	}
	scq->num_entries = size / NS_SCQE_SIZE;
	scq->base = PTR_ALIGN(scq->org, size);
	scq->next = scq->base;
	scq->last = scq->base + (scq->num_entries - 1);
	scq->tail = scq->last;
	scq->scd = scd;
	scq->num_entries = size / NS_SCQE_SIZE;
	scq->tbd_count = 0;
	init_waitqueue_head(&scq->scqfull_waitq);
	scq->full = 0;
	spin_lock_init(&scq->lock);

	for (i = 0; i < scq->num_entries; i++)
		scq->skb[i] = NULL;

	return scq;
}
