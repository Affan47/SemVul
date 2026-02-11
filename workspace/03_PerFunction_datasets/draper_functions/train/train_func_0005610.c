cf_init(struct arasan_cf_dev *acdev)
{
	struct arasan_cf_pdata *pdata = dev_get_platdata(acdev->host->dev);
	unsigned int if_clk;
	unsigned long flags;
	int ret = 0;

	ret = clk_prepare_enable(acdev->clk);
	if (ret) {
		dev_dbg(acdev->host->dev, "clock enable failed");
		return ret;
	}

	ret = clk_set_rate(acdev->clk, 166000000);
	if (ret) {
		dev_warn(acdev->host->dev, "clock set rate failed");
		clk_disable_unprepare(acdev->clk);
		return ret;
	}

	spin_lock_irqsave(&acdev->host->lock, flags);


	if_clk = CF_IF_CLK_166M;
	if (pdata && pdata->cf_if_clk <= CF_IF_CLK_200M)
		if_clk = pdata->cf_if_clk;

	writel(if_clk, acdev->vbase + CLK_CFG);

	writel(TRUE_IDE_MODE | CFHOST_ENB, acdev->vbase + OP_MODE);
	cf_interrupt_enable(acdev, CARD_DETECT_IRQ, 1);
	cf_ginterrupt_enable(acdev, 1);
	spin_unlock_irqrestore(&acdev->host->lock, flags);

	return ret;
}
