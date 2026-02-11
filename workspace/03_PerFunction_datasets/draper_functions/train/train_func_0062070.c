h4_flush(struct hci_uart *hu)
{
	struct h4_struct *h4 = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&h4->txq);

	return 0;
}
