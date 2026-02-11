ddClearGlobal(
  DdManager * table)
{
    int i,j;
    DdNode *f;
    DdNode *sentinel = &(table->sentinel);
    DdNodePtr *nodelist;
    int slots;

    for (i = 0; i < table->size; i++) {
	nodelist = table->subtables[i].nodelist;
	slots = table->subtables[i].slots;
	for (j = 0; j < slots; j++) {
	    f = nodelist[j];
	    while (f != sentinel) {
		f->next = Cudd_Regular(f->next);
		f = f->next;
	    }
	}
    }

}
