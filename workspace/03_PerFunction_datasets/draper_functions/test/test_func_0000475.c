doc_erase(struct mtd_info *mtd, struct erase_info *info)
{
	struct docg3 *docg3 = mtd->priv;
	uint64_t len;
	int block0, block1, page, ret, ofs = 0;

	doc_dbg("doc_erase(from=%lld, len=%lld\n", info->addr, info->len);

	info->state = MTD_ERASE_PENDING;
	calc_block_sector(info->addr + info->len, &block0, &block1, &page,
			  &ofs, docg3->reliable);
	ret = -EINVAL;
	if (info->addr + info->len > mtd->size || page || ofs)
		goto reset_err;

	ret = 0;
	calc_block_sector(info->addr, &block0, &block1, &page, &ofs,
			  docg3->reliable);
	mutex_lock(&docg3->cascade->lock);
	doc_set_device_id(docg3, docg3->device_id);
	doc_set_reliable_mode(docg3);
	for (len = info->len; !ret && len > 0; len -= mtd->erasesize) {
		info->state = MTD_ERASING;
		ret = doc_erase_block(docg3, block0, block1);
		block0 += 2;
		block1 += 2;
	}
	mutex_unlock(&docg3->cascade->lock);

	if (ret)
		goto reset_err;

	info->state = MTD_ERASE_DONE;
	return 0;

reset_err:
	info->state = MTD_ERASE_FAILED;
	return ret;
}
