LL1Error(int cond, Symbol *sym) {
	wprintf(L"  LL1 warning in %ls: ", curSy->name);
	if (sym != NULL) wprintf(L"%ls is ", sym->name);
	switch (cond) {
		case 1: wprintf(L"start of several alternatives\n"); break;
		case 2: wprintf(L"start & successor of deletable structure\n"); break;
		case 3: wprintf(L"an ANY node that matches no symbol\n"); break;
		case 4: wprintf(L"contents of [...] or {...} must not be deletable\n"); break;
	}
}
