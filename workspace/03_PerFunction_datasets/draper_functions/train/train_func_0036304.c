mwifiex_add_sta_entry(struct mwifiex_private *priv, const u8 *mac)
{
	struct mwifiex_sta_node *node;
	unsigned long flags;

	if (!mac)
		return NULL;

	spin_lock_irqsave(&priv->sta_list_spinlock, flags);
	node = mwifiex_get_sta_entry(priv, mac);
	if (node)
		goto done;

	node = kzalloc(sizeof(*node), GFP_ATOMIC);
	if (!node)
		goto done;

	memcpy(node->mac_addr, mac, ETH_ALEN);
	list_add_tail(&node->list, &priv->sta_list);

done:
	spin_unlock_irqrestore(&priv->sta_list_spinlock, flags);
	return node;
}
