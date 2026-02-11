getRemSetSlot() {
	unsigned int i;
	for (i = 0; i < remSet.size(); i++) {
		if (!remSet.at(i)) {
			return i;
		}

		if (i + 1 == remSet.size()) {
			remSet.resize(remSet.size() * 2);
		}
	}
	fprintf(stderr, "remSetSlotERror: no list slot found\n");
	return -1;
}
