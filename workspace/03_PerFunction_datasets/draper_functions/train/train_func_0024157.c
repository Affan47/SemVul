btrfsic_bh_end_io(struct buffer_head *bh, int uptodate)
{
	struct btrfsic_block *block = (struct btrfsic_block *)bh->b_private;
	int iodone_w_error = !uptodate;
	struct btrfsic_dev_state *dev_state;

	BUG_ON(NULL == block);
	dev_state = block->dev_state;
	if ((dev_state->state->print_mask & BTRFSIC_PRINT_MASK_END_IO_BIO_BH))
		printk(KERN_INFO
		       "bh_end_io(error=%d) for %c @%llu (%s/%llu/%d)\n",
		       iodone_w_error,
		       btrfsic_get_block_type(dev_state->state, block),
		       block->logical_bytenr, block->dev_state->name,
		       block->dev_bytenr, block->mirror_num);

	block->iodone_w_error = iodone_w_error;
	if (block->submit_bio_bh_rw & REQ_FLUSH) {
		dev_state->last_flush_gen++;
		if ((dev_state->state->print_mask &
		     BTRFSIC_PRINT_MASK_END_IO_BIO_BH))
			printk(KERN_INFO
			       "bh_end_io() new %s flush_gen=%llu\n",
			       dev_state->name, dev_state->last_flush_gen);
	}
	if (block->submit_bio_bh_rw & REQ_FUA)
		block->flush_gen = 0;

	bh->b_private = block->orig_bio_bh_private;
	bh->b_end_io = block->orig_bio_bh_end_io.bh;
	block->is_iodone = 1;
	bh->b_end_io(bh, uptodate);
}
