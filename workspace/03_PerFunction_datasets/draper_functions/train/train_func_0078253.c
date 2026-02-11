__ohamt_erase(struct ohamt_root *root,
                                  struct ohamt_slot *slot)
{
	if (!slot_is_leaf(*slot)) {
		struct ohamt_node *node = slot_to_node(root->mem, *slot);
		int i;
		for (i=0; i < set_count(node->mask); i++) {
			__ohamt_erase(root, &node->slots[i]);
		}
		__ohamt_free_slot(root, *slot);
		memset(slot, 0, sizeof(struct ohamt_slot));
	}
}
