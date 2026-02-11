blkid_probe_use_wiper(blkid_probe pr, blkid_loff_t off, blkid_loff_t size)
{
	struct blkid_chain *chn = NULL;

	if (blkid_probe_is_wiped(pr, &chn, off, size) && chn) {
		DBG(LOWPROBE, ul_debug("previously wiped area modified "
				       " -- ignore previous results"));
		blkid_probe_set_wiper(pr, 0, 0);
		blkid_probe_chain_reset_values(pr, chn);
	}
}
