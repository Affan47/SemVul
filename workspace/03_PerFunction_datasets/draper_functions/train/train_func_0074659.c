mwifiex_add_bss_prio_tbl(struct mwifiex_private *priv)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_bss_prio_node *bss_prio;
	struct mwifiex_bss_prio_tbl *tbl = adapter->bss_prio_tbl;
	unsigned long flags;

	bss_prio = kzalloc(sizeof(struct mwifiex_bss_prio_node), GFP_KERNEL);
	if (!bss_prio)
		return -ENOMEM;

	bss_prio->priv = priv;
	INIT_LIST_HEAD(&bss_prio->list);

	spin_lock_irqsave(&tbl[priv->bss_priority].bss_prio_lock, flags);
	list_add_tail(&bss_prio->list, &tbl[priv->bss_priority].bss_prio_head);
	spin_unlock_irqrestore(&tbl[priv->bss_priority].bss_prio_lock, flags);

	return 0;
}
