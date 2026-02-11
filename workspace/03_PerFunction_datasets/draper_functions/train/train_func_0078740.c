key_uses_keycode (const Key *key, guint keycode)
{
	if (key->keycodes != NULL) {
		guint *c;

		for (c = key->keycodes; *c; ++c) {
			if (*c == keycode)
				return TRUE;
		}
	}
	return FALSE;
}
