FcInitDebug (void)
{
    char    *e;

    e = getenv ("FC_DEBUG");
    if (e)
    {
        printf ("FC_DEBUG=%s\n", e);
        FcDebugVal = atoi (e);
        if (FcDebugVal < 0)
   	    FcDebugVal = 0;
    }
}
