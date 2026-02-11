scalar_expansion(Module_table *mHead)
{
    Module_table *m;

    for (m = mHead; m != NULL; m = m->next) {
	if (m->kind != MODULE_BLOCKDATA) {
	    sNum = get_max_var_entry(m->var_head);

	    ConstructPostfixTab();
	    ConstructExpScalarSet();
	    ConstructExpEntryTab();

	    TraverseBlock4ScalarExpansion(m->block_head);

	    DestructExpEntryTab();
	    DestructExpScalarSet();
	    DestructPostfixTab();
	}
    }
}
