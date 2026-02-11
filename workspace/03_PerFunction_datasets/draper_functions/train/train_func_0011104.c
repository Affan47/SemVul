syntax_end_parsing(lnum)
    linenr_T	lnum;
{
    synstate_T	*sp;

    sp = syn_stack_find_entry(lnum);
    if (sp != NULL && sp->sst_lnum < lnum)
	sp = sp->sst_next;

    if (sp != NULL && sp->sst_change_lnum != 0)
	sp->sst_change_lnum = lnum;
}
