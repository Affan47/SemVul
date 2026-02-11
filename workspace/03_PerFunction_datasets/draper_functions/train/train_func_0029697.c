winopenuri(pdfapp_t *app, char *buf)
{
	char *browser = getenv("BROWSER");
	if (!browser)
	{
#ifdef __APPLE__
		browser = "open";
#else
		browser = "xdg-open";
#endif
	}
	if (fork() == 0)
	{
		execlp(browser, browser, buf, (char*)0);
		fprintf(stderr, "cannot exec '%s'\n", browser);
		exit(0);
	}
}
