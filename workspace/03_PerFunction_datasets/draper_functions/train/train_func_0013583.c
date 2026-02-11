sort_file_node_list(struct gr_learn_file_node *root)
{
	struct gr_learn_file_node **filelist;
	int count = 0;
	int i;
	int list_size = 1;
	int num_merges;
	int left_size, right_size;
	struct gr_learn_file_node *cur, *left, *right, *end;
	const char *basename;
	unsigned int baselen;

	if (root == NULL)
		return;

	filelist = &root->leaves;

	if (*filelist == NULL)
		return;

	basename = root->filename;
	baselen = strlen(basename);

	if (baselen == 1)
		baselen = 0;

	for_each_list_entry(cur, *filelist) {
		sort_file_node_list(cur);
		count++;
	}

	if (count < 2)
		return;

	while (1) {
		left = *filelist;
		*filelist = NULL;
		end = NULL;

		num_merges = 0;

		while (left) {
			num_merges++;
			right = left;
			left_size = 0;

			for (i = 0; i < list_size; i++) {
				left_size++;
				right = right->next;
				if (right == NULL)
					break;
			}

			right_size = list_size;

			while (left_size > 0 || (right_size > 0 && right != NULL)) {
				if (left_size == 0) {
					cur = right;
					right = right->next;
					right_size--;
				} else if (right_size == 0 || right == NULL ||
					   strcmp(left->filename + baselen + 1, right->filename + baselen + 1) <= 0) {
					cur = left;
					left = left->next;
					left_size--;
				} else {
					cur = right;
					right = right->next;
					right_size--;
				}

				if (end)
					end->next = cur;
				else
					*filelist = cur;
				cur->prev = end;
				end = cur;
			}

			left = right;
		}

		end->next = NULL;

		if (num_merges <= 1)
			return;

		list_size <<= 1;
	}

	return;
}
