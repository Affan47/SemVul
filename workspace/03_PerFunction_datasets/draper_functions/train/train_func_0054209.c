poll_catas(unsigned long dev_ptr)
{
	struct mthca_dev *dev = (struct mthca_dev *) dev_ptr;
	int i;

	for (i = 0; i < dev->catas_err.size; ++i)
		if (readl(dev->catas_err.map + i)) {
			handle_catas(dev);
			return;
		}

	mod_timer(&dev->catas_err.timer,
		  round_jiffies(jiffies + MTHCA_CATAS_POLL_INTERVAL));
}
