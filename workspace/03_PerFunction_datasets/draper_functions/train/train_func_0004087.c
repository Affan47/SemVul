print_leaf(struct buffer_head *bh, int print_mode, int first,
		      int last)
{
	struct block_head *blkh;
	struct item_head *ih;
	int i, nr;
	int from, to;

	if (!B_IS_ITEMS_LEVEL(bh))
		return 1;

	check_leaf(bh);

	blkh = B_BLK_HEAD(bh);
	ih = item_head(bh, 0);
	nr = blkh_nr_item(blkh);

	printk
	    ("\n===================================================================\n");
	reiserfs_printk("LEAF NODE (%ld) contains %z\n", bh->b_blocknr, bh);

	if (!(print_mode & PRINT_LEAF_ITEMS)) {
		reiserfs_printk("FIRST ITEM_KEY: %k, LAST ITEM KEY: %k\n",
				&(ih->ih_key), &((ih + nr - 1)->ih_key));
		return 0;
	}

	if (first < 0 || first > nr - 1)
		from = 0;
	else
		from = first;

	if (last < 0 || last > nr)
		to = nr;
	else
		to = last;

	ih += from;
	printk
	    ("-------------------------------------------------------------------------------\n");
	printk
	    ("|##|   type    |           key           | ilen | free_space | version | loc  |\n");
	for (i = from; i < to; i++, ih++) {
		printk
		    ("-------------------------------------------------------------------------------\n");
		reiserfs_printk("|%2d| %h |\n", i, ih);
		if (print_mode & PRINT_LEAF_ITEMS)
			op_print_item(ih, ih_item_body(bh, ih));
	}

	printk
	    ("===================================================================\n");

	return 0;
}
