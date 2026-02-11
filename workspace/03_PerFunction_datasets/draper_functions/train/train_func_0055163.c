c_varop(int argc, int *argt)
{
    int i;

    if (argc < 1)
	return E_ARG_LO;

    argt[0] = CELL_TYPE;

    for (i = 1; i <= argc; i++)
	if (argt[i] == FCELL_TYPE)
	    argt[0] = FCELL_TYPE;

    for (i = 1; i <= argc; i++)
	if (argt[i] == DCELL_TYPE)
	    argt[0] = DCELL_TYPE;

    for (i = 1; i <= argc; i++)
	argt[i] = argt[0];

    return 0;
}
