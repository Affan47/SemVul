MatchLiteral(wchar_t* s, Symbol *sym) {
	wchar_t *subS = coco_string_create(s, 1, coco_string_length(s)-2);
	s = tab->Unescape(subS);
	coco_string_delete(subS);
	int i, len = coco_string_length(s);
	State *state = firstState;
	Action *a = NULL;
	for (i = 0; i < len; i++) {
		a = FindAction(state, s[i]);
		if (a == NULL) break;
		state = a->target->state;
	}

	if (i != len || state->endOf == NULL) {
		state = firstState; i = 0; a = NULL;
		dirtyDFA = true;
	}
	for (; i < len; i++) {
		State *to = NewState();
		NewTransition(state, to, Node::chr, s[i], Node::normalTrans);
		state = to;
	}
	coco_string_delete(s);
	Symbol *matchedSym = state->endOf;
	if (state->endOf == NULL) {
		state->endOf = sym;
	} else if (matchedSym->tokenKind == Symbol::fixedToken || (a != NULL && a->tc == Node::contextTrans)) {

		wchar_t format[200];
		coco_swprintf(format, 200, L"tokens %ls and %ls cannot be distinguished", sym->name, matchedSym->name);
		parser->SemErr(format);
	} else {
		matchedSym->tokenKind = Symbol::classLitToken;
		sym->tokenKind = Symbol::litToken;
	}
}
