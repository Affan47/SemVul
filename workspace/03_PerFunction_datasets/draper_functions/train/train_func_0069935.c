search_module_table(module_kind	kind,
		    int		entry)
{
    Module_table	*mpt;

    mpt = module_head;
    while (mpt != NULL) {
	if ((mpt->kind == kind)&&(mpt->entry == entry)) {
	    return(mpt);
	} else
	    mpt = mpt->next;
    }
    return(mpt);
}
