rrpc_map_init(struct rrpc *rrpc)
{
	struct nvm_dev *dev = rrpc->dev;
	sector_t i;
	int ret;

	rrpc->trans_map = vzalloc(sizeof(struct rrpc_addr) * rrpc->nr_pages);
	if (!rrpc->trans_map)
		return -ENOMEM;

	rrpc->rev_trans_map = vmalloc(sizeof(struct rrpc_rev_addr)
							* rrpc->nr_pages);
	if (!rrpc->rev_trans_map)
		return -ENOMEM;

	for (i = 0; i < rrpc->nr_pages; i++) {
		struct rrpc_addr *p = &rrpc->trans_map[i];
		struct rrpc_rev_addr *r = &rrpc->rev_trans_map[i];

		p->addr = ADDR_EMPTY;
		r->addr = ADDR_EMPTY;
	}

	if (!dev->ops->get_l2p_tbl)
		return 0;


	ret = dev->ops->get_l2p_tbl(dev, 0, dev->total_pages,
							rrpc_l2p_update, rrpc);
	if (ret) {
		pr_err("nvm: rrpc: could not read L2P table.\n");
		return -EINVAL;
	}

	return 0;
}
