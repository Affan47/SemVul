match_name(DirEntry **epp, const char *name)
{
    for (DirEntry *ep; ((ep = *epp) != NULL); epp = &ep->next)
	if (!strcmp(ep->name(), name))
	    return epp;
    return NULL;
}
