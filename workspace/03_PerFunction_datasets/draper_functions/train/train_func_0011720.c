loadGtkSymbols( void * library, FN_TABLE * table) {
	int i = 0;
	void * fn;
	for (i = 0; table[i].fnName != NULL; i++) {
		fn = findSymbol(library, table[i].fnName);
		if (fn != 0)
			*(table[i].fnPtr) = fn;
		else
			return -1;
	}
	return 0;
}
