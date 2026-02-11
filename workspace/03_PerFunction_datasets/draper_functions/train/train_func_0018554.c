uwb_rc_new_index(void)
{
	int index = 0;

	for (;;) {
		if (!uwb_rc_find_by_index(index))
			return index;
		if (++index < 0)
			index = 0;
	}
}
