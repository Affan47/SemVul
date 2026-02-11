sparse_keymap_getkeycode(struct input_dev *dev,
				    struct input_keymap_entry *ke)
{
	const struct key_entry *key;

	if (dev->keycode) {
		key = sparse_keymap_locate(dev, ke);
		if (key && key->type == KE_KEY) {
			ke->keycode = key->keycode;
			if (!(ke->flags & INPUT_KEYMAP_BY_INDEX))
				ke->index =
					sparse_keymap_get_key_index(dev, key);
			ke->len = sizeof(key->code);
			memcpy(ke->scancode, &key->code, sizeof(key->code));
			return 0;
		}
	}

	return -EINVAL;
}
