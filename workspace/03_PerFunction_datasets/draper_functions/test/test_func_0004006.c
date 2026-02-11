isl_blk_is_error(struct isl_blk block)
{
	return block.size == -1 && block.data == NULL;
}
