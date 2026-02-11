brasero_file_node_unlink (BraseroFileNode *node)
{
	BraseroFileNode *iter;
	BraseroImport *import;

	if (!node->parent)
		return;

	iter = BRASERO_FILE_NODE_CHILDREN (node->parent);


	if (!node->is_grafted
	&&  !node->is_imported
	&&  !BRASERO_FILE_NODE_VIRTUAL (node)) {
		BraseroFileNode *parent;


		for (parent = node->parent; parent && !parent->is_root; parent = parent->parent) {
			parent->union3.sectors -= BRASERO_FILE_NODE_SECTORS (node);
			if (parent->is_grafted)
				break;
		}
	}

	node->is_deep = FALSE;

	if (iter == node) {
		node->parent->union2.children = node->next;
		node->parent = NULL;
		node->next = NULL;
		return;
	}

	for (; iter->next; iter = iter->next) {
		if (iter->next == node) {
			iter->next = node->next;
			node->parent = NULL;
			node->next = NULL;
			return;
		}
	}

	if (!node->is_imported || !node->parent->has_import)
		return;


	import = BRASERO_FILE_NODE_IMPORT (node->parent);
	iter = import->replaced;

	if (iter == node) {
		import->replaced = iter->next;
		node->parent = NULL;
		node->next = NULL;
		return;
	}

	for (; iter->next; iter = iter->next) {
		if (iter->next == node) {
			iter->next = node->next;
			node->parent = NULL;
			node->next = NULL;
			return;
		}
	}
}
