clear() {
	cur_text = NULL;
	for (int i = 0; i < max_pages; i++) {
		if (text[i]) {
			delete(text[i]);
			text[i] = NULL;
		}
	}
}
