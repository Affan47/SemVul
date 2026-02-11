fill_key(struct input_event *ev, unsigned long mask, unsigned int key)
{
	size_t		i;

	for (i = 0; i < ARRAY_SIZE(KEY_DEFS); ++i) {
		if (KEY_DEFS[i].mask == mask &&
		    KEY_DEFS[i].key  == key) {
			ev[0].type  = EV_MSC;
			ev[0].code  = MSC_SCAN;
			ev[0].value = i;

			ev[1].type  = EV_KEY;
			ev[1].code  = KEY_DEFS[i].code;

			return true;
		}
	}

	return false;
}
