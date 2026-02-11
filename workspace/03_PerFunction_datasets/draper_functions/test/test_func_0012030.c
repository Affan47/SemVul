internal_delete_childs(struct buffer_info *cur_bi, int from, int n)
{
	int i_from;

	i_from = (from == 0) ? from : from - 1;


	internal_delete_pointers_items(cur_bi, from, i_from, n);
}
