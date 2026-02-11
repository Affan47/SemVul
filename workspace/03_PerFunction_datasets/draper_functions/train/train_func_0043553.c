slic_cmdq_reset(struct adapter *adapter)
{
	struct slic_hostcmd *hcmd;
	struct sk_buff *skb;
	u32 outstanding;
	unsigned long flags;

	spin_lock_irqsave(&adapter->cmdq_free.lock, flags);
	spin_lock(&adapter->cmdq_done.lock);
	outstanding = adapter->cmdq_all.count - adapter->cmdq_done.count;
	outstanding -= adapter->cmdq_free.count;
	hcmd = adapter->cmdq_all.head;
	while (hcmd) {
		if (hcmd->busy) {
			skb = hcmd->skb;
			hcmd->busy = 0;
			hcmd->skb = NULL;
			dev_kfree_skb_irq(skb);
		}
		hcmd = hcmd->next_all;
	}
	adapter->cmdq_free.count = 0;
	adapter->cmdq_free.head = NULL;
	adapter->cmdq_free.tail = NULL;
	adapter->cmdq_done.count = 0;
	adapter->cmdq_done.head = NULL;
	adapter->cmdq_done.tail = NULL;
	adapter->cmdq_free.head = adapter->cmdq_all.head;
	hcmd = adapter->cmdq_all.head;
	while (hcmd) {
		adapter->cmdq_free.count++;
		hcmd->next = hcmd->next_all;
		hcmd = hcmd->next_all;
	}
	if (adapter->cmdq_free.count != adapter->cmdq_all.count) {
		dev_err(&adapter->netdev->dev,
			"free_count %d != all count %d\n",
			adapter->cmdq_free.count, adapter->cmdq_all.count);
	}
	spin_unlock(&adapter->cmdq_done.lock);
	spin_unlock_irqrestore(&adapter->cmdq_free.lock, flags);
}
