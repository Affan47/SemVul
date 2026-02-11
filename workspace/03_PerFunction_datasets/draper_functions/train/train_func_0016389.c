free_tx_desc(struct adapter *adap, struct sge_txq *q,
			 unsigned int n, bool unmap)
{
	struct tx_sw_desc *d;
	unsigned int cidx = q->cidx;
	struct device *dev = adap->pdev_dev;

	d = &q->sdesc[cidx];
	while (n--) {
		if (d->skb) {
			if (unmap)
				unmap_sgl(dev, d->skb, d->sgl, q);
			dev_consume_skb_any(d->skb);
			d->skb = NULL;
		}
		++d;
		if (++cidx == q->size) {
			cidx = 0;
			d = q->sdesc;
		}
	}
	q->cidx = cidx;
}
