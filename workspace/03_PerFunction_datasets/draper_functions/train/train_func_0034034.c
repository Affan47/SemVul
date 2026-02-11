ohamt_delete_all(struct ohamt_root *root,
		      void (*fun)(void *ud, uint64_t item), void *ud)
{
	struct ohamt_state s;
	while (slot_to_node(root->mem, root->slot) != NULL) {
		s.level = 0;
		s.ptr[0] = &root->slot;
		uint64_t found_item = __ohamt_down(root, &s);
		uint128_t hash = root->hash(root->hash_ud, found_item);
		__ohamt_delete(root, hash, &s);

		fun(ud, found_item);
	}
}
