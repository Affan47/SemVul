serve_set (char *arg)
{
# ifdef PROXY_SUPPORT
    if (reprocessing) return;
# endif


    variable_set (arg);
}
