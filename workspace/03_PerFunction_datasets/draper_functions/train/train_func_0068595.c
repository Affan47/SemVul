c_int(int argc, int *argt)
{
    if (argc < 1)
	return E_ARG_LO;
    if (argc > 1)
	return E_ARG_HI;

    argt[0] = CELL_TYPE;


    return 0;
}
