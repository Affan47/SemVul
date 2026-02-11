qbuf_scan(struct orinoco_private *priv, void *buf,
		      int len, int type)
{
	struct orinoco_scan_data *sd;
	unsigned long flags;

	sd = kmalloc(sizeof(*sd), GFP_ATOMIC);
	if (!sd)
		return;

	sd->buf = buf;
	sd->len = len;
	sd->type = type;

	spin_lock_irqsave(&priv->scan_lock, flags);
	list_add_tail(&sd->list, &priv->scan_list);
	spin_unlock_irqrestore(&priv->scan_lock, flags);

	schedule_work(&priv->process_scan);
}
