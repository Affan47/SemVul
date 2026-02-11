SetTransparency(Uint8 t, bool bRecursive) {
	(*_mid)[UNPRESSED].transparency = t;
	(*_mid)[PRESSED].transparency = t;
	(*_mid)[HIGHLITED].transparency = t;

	if(!bRecursive || (GetChildList() == NULL)) {
		return;
	}

	for(PG_Widget* i = GetChildList()->first(); i != NULL; i = i->next()) {
		i->SetTransparency(t, true);
	}
}
