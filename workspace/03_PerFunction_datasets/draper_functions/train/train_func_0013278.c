btrfsic_block_link_free(struct btrfsic_block_link *l)
{
	BUG_ON(!(NULL == l || BTRFSIC_BLOCK_LINK_MAGIC_NUMBER == l->magic_num));
	kfree(l);
}
