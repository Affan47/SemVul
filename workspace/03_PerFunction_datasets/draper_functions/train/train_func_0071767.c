sparse_keymap_locate(struct input_dev *dev,
					const struct input_keymap_entry *ke)
{
	struct key_entry *key;
	unsigned int scancode;

	if (ke->flags & INPUT_KEYMAP_BY_INDEX)
		key = sparse_keymap_entry_by_index(dev, ke->index);
	else if (input_scancode_to_scalar(ke, &scancode) == 0)
		key = sparse_keymap_entry_from_scancode(dev, scancode);
	else
		key = NULL;

	return key;
}
