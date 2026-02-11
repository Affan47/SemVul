uci_debug(char *str)
{
    if (uci_logfile)
    {
        fprintf(uci_logfile, "%d: %s\n", getpid(), str);
        fflush(uci_logfile);
    }
}
