DEH_PointerInit(void)
{
    int i;


    for (i=0; i<NUMSTATES; ++i)
        codeptrs[i] = states[i].action;
}
