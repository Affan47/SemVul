node_detach(node_t* parent, node_t* child) {
	if (!parent || !child) return -1;
	int index = node_list_remove(parent->children, child);
	if (index >= 0) {
		parent->count--;
	}
	return index;
}
