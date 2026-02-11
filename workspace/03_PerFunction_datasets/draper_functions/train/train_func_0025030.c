call_ll_exitfuncs(void)
{
    while (nexitfuncs > 0)
        (*exitfuncs[--nexitfuncs])();

    fflush(stdout);
    fflush(stderr);
}
