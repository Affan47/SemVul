leavemac()
{
    register struct macroposition *mpptr;

    do
    {
	mpptr = &macrostack[maclevel - 1];
	if (mpptr->inparam)
	{
	    lineptr = ++mpptr->paramspot;
	    mpptr->inparam = FALSE;
	}
	else
	{
	    mpptr->symptr->name.namea[0] &= 0x7F;
	    ch = *++lineptr;
	    if (ch != 0)
	    {
		mpptr->paramspot = lineptr;
		lineptr = mpptr->paramlist[ch - 1];
		mpptr->inparam = TRUE;
	    }
	    else
	    {
		lineptr = mpptr->maclineptr;
		if (mpptr->nparam != 0)
		{
		    register char **paramlist;

#ifdef TS
ts_s_macparam_tot -= sizeof *paramlist * mpptr->nparam;
#endif
		    paramlist = mpptr->paramlist;
		    do
{
#ifdef TS
ts_s_macparam_string_alloced_tot -= strchr(*paramlist, EOL) - *paramlist + 1;
#endif
			ourfree(*paramlist++);
}
		    while (--mpptr->nparam != 0);
		    ourfree(mpptr->paramlist);
		}
		--maclevel;
	    }
	}
    }
    while ((ch = *lineptr) == EOL && maclevel != 0);
}
