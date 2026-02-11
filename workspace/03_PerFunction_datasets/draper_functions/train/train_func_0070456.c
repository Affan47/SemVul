pager_open(void)
{


    if (!background() && isatty(0) && isatty(1))
    {
        pager = getenv("PAGER");
        if (!pager || !*pager)
            pager = "more";
    }
    else
        pager = 0;

#ifdef HAVE_ATEXIT


    atexit(cleanup);
#endif


    if (pager)
    {
        out = pipe_open(pager);
        if (!out)
        {
            pager = 0;
            out = stdout;
        }
    }
    else
        out = stdout;
    return out;
}
