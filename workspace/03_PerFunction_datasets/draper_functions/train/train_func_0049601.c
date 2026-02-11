super_error(struct layer2 *l2, struct sk_buff *skb)
{
	if (skb->len != l2addrsize(l2) +
	    (test_bit(FLG_MOD128, &l2->flag) ? 2 : 1))
		return 'N';
	return 0;
}
