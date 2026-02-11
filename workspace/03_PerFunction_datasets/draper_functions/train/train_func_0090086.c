sparse_keymap_report_event(struct input_dev *dev, unsigned int code,
				unsigned int value, bool autorelease)
{
	const struct key_entry *ke =
		sparse_keymap_entry_from_scancode(dev, code);
	struct key_entry unknown_ke;

	if (ke) {
		sparse_keymap_report_entry(dev, ke, value, autorelease);
		return true;
	}


	unknown_ke.type = KE_KEY;
	unknown_ke.code = code;
	unknown_ke.keycode = KEY_UNKNOWN;
	sparse_keymap_report_entry(dev, &unknown_ke, value, true);

	return false;
}
