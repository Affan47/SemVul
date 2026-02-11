setva(struct layer2 *l2, unsigned int nr)
{
	struct sk_buff	*skb;

	while (l2->va != nr) {
		l2->va++;
		if (test_bit(FLG_MOD128, &l2->flag))
			l2->va %= 128;
		else
			l2->va %= 8;
		if (l2->windowar[l2->sow]) {
			skb_trim(l2->windowar[l2->sow], 0);
			skb_queue_tail(&l2->tmp_queue, l2->windowar[l2->sow]);
			l2->windowar[l2->sow] = NULL;
		}
		l2->sow = (l2->sow + 1) % l2->window;
	}
	skb = skb_dequeue(&l2->tmp_queue);
	while (skb) {
		dev_kfree_skb(skb);
		skb = skb_dequeue(&l2->tmp_queue);
	}
}
