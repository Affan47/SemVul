printipaddr(opt, printer, arg)
    option_t *opt;
    void (*printer) __P((void *, char *, ...));
    void *arg;
{
	ipcp_options *wo = &ipcp_wantoptions[0];

	if (wo->ouraddr != 0)
		printer(arg, "%I", wo->ouraddr);
	printer(arg, ":");
	if (wo->hisaddr != 0)
		printer(arg, "%I", wo->hisaddr);
}
