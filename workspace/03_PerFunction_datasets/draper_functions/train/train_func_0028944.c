find_aino (Unit *unit, uaecptr lock, const TCHAR *name, int *err)
{
	a_inode *a;

	if (lock) {
		a_inode *olda = lookup_aino (unit, get_long (lock + 4));
		if (olda == 0) {

			a = get_aino (unit, &unit->rootnode, name, err);
		} else {
			TRACE((_T("aino: 0x%08lx"), (unsigned long int)olda->uniq));
			TRACE((_T(" \"%s\"\n"), olda->nname));
			a = get_aino (unit, olda, name, err);
		}
	} else {
		a = get_aino (unit, &unit->rootnode, name, err);
	}
	if (a) {
		TRACE((_T("aino=\"%s\"\n"), a->nname));
	}
	aino_test (a);
	return a;
}
