stackTablePop ( tStackTable* s ) {
	if (!stackTableEmpty(s)) {
		s->top--;
	}
}
