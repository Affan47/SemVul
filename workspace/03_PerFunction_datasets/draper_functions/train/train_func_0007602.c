gf_node_list_get_child(GF_ChildNodeItem *list, s32 pos)
{
	s32 cur_pos = 0;
	while (list) {
		if (pos==cur_pos) return list->node;
		if ((pos<0) && !list->next) return list->node;
		list = list->next;
		cur_pos++;
	}
	return NULL;
}
