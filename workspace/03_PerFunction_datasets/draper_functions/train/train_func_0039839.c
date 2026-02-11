pch_gbe_irq_disable(struct pch_gbe_adapter *adapter)
{
	struct pch_gbe_hw *hw = &adapter->hw;

	atomic_inc(&adapter->irq_sem);
	iowrite32(0, &hw->reg->INT_EN);
	ioread32(&hw->reg->INT_ST);
	synchronize_irq(adapter->pdev->irq);

	netdev_dbg(adapter->netdev, "INT_EN reg : 0x%08x\n",
		   ioread32(&hw->reg->INT_EN));
}
