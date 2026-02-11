Release() {
	LexerMinder *lm;
	LexerMinder *lmNext;
	lm = first;
	while (NULL != lm) {
		lmNext = lm->next;
		delete lm->self;
		delete lm;
		lm = lmNext;
	}

	first = NULL;
	last = NULL;
}
