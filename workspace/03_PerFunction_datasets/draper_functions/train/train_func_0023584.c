Clear() {
	if (NULL != first) {
		LexerLibrary *cur = first;
		LexerLibrary *next;
		while (cur) {
			next = cur->next;
			delete cur;
			cur = next;
		}
		first = NULL;
		last = NULL;
	}
}
