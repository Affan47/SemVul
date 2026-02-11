erase_block(struct partition *part, int block)
{
	struct erase_info *erase;
	int rc = -ENOMEM;

	erase = kmalloc(sizeof(struct erase_info), GFP_KERNEL);
	if (!erase)
		goto err;

	erase->mtd = part->mbd.mtd;
	erase->callback = erase_callback;
	erase->addr = part->blocks[block].offset;
	erase->len = part->block_size;
	erase->priv = (u_long)part;

	part->blocks[block].state = BLOCK_ERASING;
	part->blocks[block].free_sectors = 0;

	rc = mtd_erase(part->mbd.mtd, erase);

	if (rc) {
		printk(KERN_ERR PREFIX "erase of region %llx,%llx on '%s' "
				"failed\n", (unsigned long long)erase->addr,
				(unsigned long long)erase->len, part->mbd.mtd->name);
		kfree(erase);
	}

err:
	return rc;
}
