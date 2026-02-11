rrpc_capacity(void *private)
{
	struct rrpc *rrpc = private;
	struct nvm_dev *dev = rrpc->dev;
	sector_t reserved, provisioned;


	reserved = rrpc->nr_luns * dev->max_pages_per_blk * 4;
	provisioned = rrpc->nr_pages - reserved;

	if (reserved > rrpc->nr_pages) {
		pr_err("rrpc: not enough space available to expose storage.\n");
		return 0;
	}

	sector_div(provisioned, 10);
	return provisioned * 9 * NR_PHY_IN_LOG;
}
