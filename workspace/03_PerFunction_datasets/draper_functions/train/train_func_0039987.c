pin_stats_count_object_from_tree (GCObject *object, size_t size, PinStatAddress *node, int *pin_types)
{
	char *obj = (char*)object;
	if (!node)
		return;
	if (node->addr >= obj && node->addr < obj + size) {
		int i;
		for (i = 0; i < PIN_TYPE_MAX; ++i) {
			int pin_bit = 1 << i;
			if (!(*pin_types & pin_bit) && (node->pin_types & pin_bit)) {
				pinned_byte_counts [i] += size;
				*pin_types |= pin_bit;
			}
		}
	}
	if (obj < node->addr)
		pin_stats_count_object_from_tree (object, size, node->left, pin_types);
	if (obj + size - 1 > node->addr)
		pin_stats_count_object_from_tree (object, size, node->right, pin_types);
}
