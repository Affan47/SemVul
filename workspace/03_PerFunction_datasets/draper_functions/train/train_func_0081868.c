kgdboc_unregister_kbd(void)
{
	int i;

	for (i = 0; i < kdb_poll_idx; i++) {
		if (kdb_poll_funcs[i] == kdb_get_kbd_char) {
			kdb_poll_idx--;
			kdb_poll_funcs[i] = kdb_poll_funcs[kdb_poll_idx];
			kdb_poll_funcs[kdb_poll_idx] = NULL;
			i--;
		}
	}
	flush_work(&kgdboc_restore_input_work);
}
