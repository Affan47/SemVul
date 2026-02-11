__ohamt_insert_leaf(struct ohamt_root *root,
			       struct ohamt_state *s,
			       uint128_t item_hash, uint64_t item,
			       uint128_t leaf_hash, uint64_t leaf)
{
        int leaf_slice = slice_get(leaf_hash, s->level);
        int item_slice = slice_get(item_hash, s->level);
        if (leaf_slice != item_slice) {
		*s->ptr[s->level] = __ohamt_new_slot2(root,
						      item, item_slice,
						      leaf, leaf_slice);
        } else {
		struct ohamt_slot slot = __ohamt_new_slot1(root,
							   item_slice,
							   leaf_to_slot(OHAMT_NOT_FOUND));
		struct ohamt_node *node =  slot_to_node(root->mem, slot);
                *s->ptr[s->level] = slot;
                s->ptr[s->level + 1] = &node->slots[0];
                s->level += 1;
                __ohamt_insert_leaf(root, s, item_hash, item, leaf_hash, leaf);
        }
}
