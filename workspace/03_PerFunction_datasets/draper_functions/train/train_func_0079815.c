namDebugResource(const AjPTable rstable)
{
    ajulong i;
    ajulong nkeys;
    AjPStr *names = NULL;
    AjPStr *values = NULL;

    nkeys = ajTableToarrayKeysValues(rstable,
                                     (void***) &names, (void***) &values);

   for(i=0UL; i < nkeys; i++)
	if(ajStrGetLen(values[i]))
	    namUser("\t%S: %S\n", names[i], values[i]);

    AJFREE(names);
    AJFREE(values);

    return;
}
