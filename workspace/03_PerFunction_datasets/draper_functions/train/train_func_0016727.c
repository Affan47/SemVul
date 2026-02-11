libmpq__huffman_previous_item(struct huffman_tree_item_s *hi, long value) {


	if (PTR_INT(hi->prev) < 0) {


		return PTR_NOT(hi->prev);
	}


	if (value < 0) {


		value = hi - hi->next->prev;
	}


	return hi->prev + value;
}
