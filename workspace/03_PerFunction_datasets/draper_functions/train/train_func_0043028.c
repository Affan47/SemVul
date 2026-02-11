rrpc_init(struct nvm_dev *dev, struct gendisk *tdisk,
						int lun_begin, int lun_end)
{
	struct request_queue *bqueue = dev->q;
	struct request_queue *tqueue = tdisk->queue;
	struct rrpc *rrpc;
	int ret;

	if (!(dev->identity.dom & NVM_RSP_L2P)) {
		pr_err("nvm: rrpc: device does not support l2p (%x)\n",
							dev->identity.dom);
		return ERR_PTR(-EINVAL);
	}

	rrpc = kzalloc(sizeof(struct rrpc), GFP_KERNEL);
	if (!rrpc)
		return ERR_PTR(-ENOMEM);

	rrpc->instance.tt = &tt_rrpc;
	rrpc->dev = dev;
	rrpc->disk = tdisk;

	bio_list_init(&rrpc->requeue_bios);
	spin_lock_init(&rrpc->bio_lock);
	INIT_WORK(&rrpc->ws_requeue, rrpc_requeue);

	rrpc->nr_luns = lun_end - lun_begin + 1;


	atomic_set(&rrpc->next_lun, -1);

	ret = rrpc_luns_init(rrpc, lun_begin, lun_end);
	if (ret) {
		pr_err("nvm: rrpc: could not initialize luns\n");
		goto err;
	}

	rrpc->poffset = dev->sec_per_lun * lun_begin;
	rrpc->lun_offset = lun_begin;

	ret = rrpc_core_init(rrpc);
	if (ret) {
		pr_err("nvm: rrpc: could not initialize core\n");
		goto err;
	}

	ret = rrpc_map_init(rrpc);
	if (ret) {
		pr_err("nvm: rrpc: could not initialize maps\n");
		goto err;
	}

	ret = rrpc_blocks_init(rrpc);
	if (ret) {
		pr_err("nvm: rrpc: could not initialize state for blocks\n");
		goto err;
	}

	ret = rrpc_luns_configure(rrpc);
	if (ret) {
		pr_err("nvm: rrpc: not enough blocks available in LUNs.\n");
		goto err;
	}

	ret = rrpc_gc_init(rrpc);
	if (ret) {
		pr_err("nvm: rrpc: could not initialize gc\n");
		goto err;
	}


	blk_queue_logical_block_size(tqueue, queue_physical_block_size(bqueue));
	blk_queue_max_hw_sectors(tqueue, queue_max_hw_sectors(bqueue));

	pr_info("nvm: rrpc initialized with %u luns and %llu pages.\n",
			rrpc->nr_luns, (unsigned long long)rrpc->nr_pages);

	mod_timer(&rrpc->gc_timer, jiffies + msecs_to_jiffies(10));

	return rrpc;
err:
	rrpc_free(rrpc);
	return ERR_PTR(ret);
}
