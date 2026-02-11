bar_has_type(bool horiz) {
	for (int bar = 1; bar <= g_nbar; bar++) {
		if (horiz == br[bar]->horiz) return true;
	}
	return false;
}
