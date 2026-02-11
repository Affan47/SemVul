panel_bind_key(const char *name, const char *press,
					    const char *repeat,
					    const char *release)
{
	struct logical_input *key;

	key = kzalloc(sizeof(*key), GFP_KERNEL);
	if (!key)
		return NULL;

	if (!input_name2mask(name, &key->mask, &key->value, &scan_mask_i,
			     &scan_mask_o)) {
		kfree(key);
		return NULL;
	}

	key->type = INPUT_TYPE_KBD;
	key->state = INPUT_ST_LOW;
	key->rise_time = 1;
	key->fall_time = 1;

	strncpy(key->u.kbd.press_str, press, sizeof(key->u.kbd.press_str));
	strncpy(key->u.kbd.repeat_str, repeat, sizeof(key->u.kbd.repeat_str));
	strncpy(key->u.kbd.release_str, release,
		sizeof(key->u.kbd.release_str));
	list_add(&key->list, &logical_inputs);
	return key;
}
