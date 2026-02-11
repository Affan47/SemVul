leaf_insert_into_buf(struct buffer_info *bi, int before,
			  struct item_head * const inserted_item_ih,
			  const char * const inserted_item_body,
			  int zeros_number)
{
	struct buffer_head *bh = bi->bi_bh;
	int nr, free_space;
	struct block_head *blkh;
	struct item_head *ih;
	int i;
	int last_loc, unmoved_loc;
	char *to;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);
	free_space = blkh_free_space(blkh);


	RFALSE(free_space < ih_item_len(inserted_item_ih) + IH_SIZE,
	       "vs-10170: not enough free space in block %z, new item %h",
	       bh, inserted_item_ih);
	RFALSE(zeros_number > ih_item_len(inserted_item_ih),
	       "vs-10172: zero number == %d, item length == %d",
	       zeros_number, ih_item_len(inserted_item_ih));


	ih = item_head(bh, before);


	last_loc = nr ? ih_location(&ih[nr - before - 1]) : bh->b_size;
	unmoved_loc = before ? ih_location(ih - 1) : bh->b_size;

	memmove(bh->b_data + last_loc - ih_item_len(inserted_item_ih),
		bh->b_data + last_loc, unmoved_loc - last_loc);

	to = bh->b_data + unmoved_loc - ih_item_len(inserted_item_ih);
	memset(to, 0, zeros_number);
	to += zeros_number;


	if (inserted_item_body)
		memmove(to, inserted_item_body,
			ih_item_len(inserted_item_ih) - zeros_number);
	else
		memset(to, '\0', ih_item_len(inserted_item_ih) - zeros_number);


	memmove(ih + 1, ih, IH_SIZE * (nr - before));
	memmove(ih, inserted_item_ih, IH_SIZE);


	for (i = before; i < nr + 1; i++) {
		unmoved_loc -= ih_item_len(&ih[i - before]);
		put_ih_location(&ih[i - before], unmoved_loc);
	}


	set_blkh_nr_item(blkh, blkh_nr_item(blkh) + 1);
	set_blkh_free_space(blkh,
			    free_space - (IH_SIZE +
					  ih_item_len(inserted_item_ih)));
	do_balance_mark_leaf_dirty(bi->tb, bh, 1);

	if (bi->bi_parent) {
		struct disk_child *t_dc;
		t_dc = B_N_CHILD(bi->bi_parent, bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) + (IH_SIZE +
					     ih_item_len(inserted_item_ih)));
		do_balance_mark_internal_dirty(bi->tb, bi->bi_parent, 0);
	}
}
