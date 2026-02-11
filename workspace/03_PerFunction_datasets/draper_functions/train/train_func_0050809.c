ssc_free(struct ssc_device *ssc)
{
	bool disable_clk = true;

	spin_lock(&user_lock);
	if (ssc->user)
		ssc->user--;
	else {
		disable_clk = false;
		dev_dbg(&ssc->pdev->dev, "device already free\n");
	}
	spin_unlock(&user_lock);

	if (disable_clk)
		clk_unprepare(ssc->clk);
}
