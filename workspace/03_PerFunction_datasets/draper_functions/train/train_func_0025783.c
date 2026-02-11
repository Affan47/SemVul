i2400m_net_wake_stop(struct i2400m *i2400m)
{
	struct device *dev = i2400m_dev(i2400m);
	struct sk_buff *wake_tx_skb;
	unsigned long flags;

	d_fnstart(3, dev, "(i2400m %p)\n", i2400m);


	cancel_work_sync(&i2400m->wake_tx_ws);

	spin_lock_irqsave(&i2400m->tx_lock, flags);
	wake_tx_skb = i2400m->wake_tx_skb;
	i2400m->wake_tx_skb = NULL;
	spin_unlock_irqrestore(&i2400m->tx_lock, flags);

	if (wake_tx_skb) {
		i2400m_put(i2400m);
		kfree_skb(wake_tx_skb);
	}

	d_fnend(3, dev, "(i2400m %p) = void\n", i2400m);
}
