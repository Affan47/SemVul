_nc_ripoffline(int line, int (*init) (WINDOW *, int))
{
    T((T_CALLED("_nc_ripoffline(%d, %p)"), line, init));

    if (line != 0) {

	if (ripoff_sp == 0)
	    ripoff_sp = ripoff_stack;
	if (ripoff_sp >= ripoff_stack + N_RIPS)
	    returnCode(ERR);

	ripoff_sp->line = line;
	ripoff_sp->hook = init;
	ripoff_sp++;
    }

    returnCode(OK);
}
