delete_added_keycodes(int bequiet) {
	int kc;
	for (kc = 0; kc < 0x100; kc++) {
		if (added_keysyms[kc] != NoSymbol) {
			delete_keycode(kc, bequiet);
			added_keysyms[kc] = NoSymbol;
		}
	}
}
