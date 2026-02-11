ConsoleBegin(char *id)
#else
ConsoleBegin(id)
    char *id;
#endif
{
    CONSENT *c;

    CONDDEBUG((1, "ConsoleBegin(%s) [%s:%d]", id, file, line));
    if (id == (char *)0 || id[0] == '\000') {
	if (isMaster)
	    Error("empty console name [%s:%d]", file, line);
	return;
    }
    if (parserConsoleTemp != (CONSENT *)0)
	DestroyParserDefaultOrConsole(parserConsoleTemp, (CONSENT **)0,
				      (CONSENT ***)0);
    if ((parserConsoleTemp = (CONSENT *)calloc(1, sizeof(CONSENT)))
	== (CONSENT *)0)
	OutOfMem();


    if ((c =
	 FindParserDefaultOrConsole(parserDefaults,
				    "*")) != (CONSENT *)0) {
	ApplyDefault(c, parserConsoleTemp);
    }
    if ((parserConsoleTemp->server = StrDup(id))
	== (char *)0)
	OutOfMem();
}
