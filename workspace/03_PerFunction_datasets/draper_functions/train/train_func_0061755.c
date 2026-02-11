delete_aino (Unit *unit, a_inode *aino)
{
	a_inode **aip;

	TRACE((_T("deleting aino %x\n"), aino->uniq));

	aino_test (aino);
	aino->dirty = 1;
	aino->deleted = 1;
	de_recycle_aino (unit, aino);


	if (aino->parent->exnext_count > 0) {
		int i;
		TRACE((_T("entering exkey validation\n")));
		for (i = 0; i < EXKEYS; i++) {
			ExamineKey *k = unit->examine_keys + i;
			if (k->uniq == 0)
				continue;
			if (k->aino == aino->parent) {
				TRACE((_T("Same parent found for %d\n"), i));
				if (k->curr_file == aino) {
					k->curr_file = aino->sibling;
					TRACE((_T("Advancing curr_file\n")));
				}
			}
		}
	}

	aip = &aino->parent->child;
	while (*aip != aino && *aip != 0)
		aip = &(*aip)->sibling;
	if (*aip != aino) {
		write_log (_T("Couldn't delete aino.\n"));
		return;
	}
	dispose_aino (unit, aip, aino);
}
