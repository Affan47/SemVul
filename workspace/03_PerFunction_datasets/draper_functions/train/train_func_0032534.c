indirect_print_item(struct item_head *ih, char *item)
{
	int j;
	__le32 *unp;
	__u32 prev = INT_MAX;
	int num = 0;

	unp = (__le32 *) item;

	if (ih_item_len(ih) % UNFM_P_SIZE)
		reiserfs_warning(NULL, "reiserfs-16102", "invalid item len");

	printk("%d pointers\n[ ", (int)I_UNFM_NUM(ih));
	for (j = 0; j < I_UNFM_NUM(ih); j++) {
		if (sequence_finished(prev, &num, get_block_num(unp, j))) {
			print_sequence(prev, num);
			start_new_sequence(&prev, &num, get_block_num(unp, j));
		}
	}
	print_sequence(prev, num);
	printk("]\n");
}
