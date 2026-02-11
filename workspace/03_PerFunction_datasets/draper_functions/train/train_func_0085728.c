idt77252_send_oam(struct atm_vcc *vcc, void *cell, int flags)
{
	struct atm_dev *dev = vcc->dev;
	struct idt77252_dev *card = dev->dev_data;
	struct sk_buff *skb;

	skb = dev_alloc_skb(64);
	if (!skb) {
		printk("%s: Out of memory in send_oam().\n", card->name);
		atomic_inc(&vcc->stats->tx_err);
		return -ENOMEM;
	}
	atomic_add(skb->truesize, &sk_atm(vcc)->sk_wmem_alloc);

	memcpy(skb_put(skb, 52), cell, 52);

	return idt77252_send_skb(vcc, skb, 1);
}
