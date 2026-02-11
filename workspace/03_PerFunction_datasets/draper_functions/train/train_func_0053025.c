brasero_file_node_get_pos_as_child (BraseroFileNode *node)
{
	BraseroFileNode *parent;
	BraseroFileNode *peers;
	guint pos = 0;

	if (!node)
		return 0;

	parent = node->parent;
	for (peers = BRASERO_FILE_NODE_CHILDREN (parent); peers; peers = peers->next) {
		if (peers == node)
			break;
		pos ++;
	}

	return pos;
}
