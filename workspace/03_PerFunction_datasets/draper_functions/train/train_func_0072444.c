ConfigItemLogfile(char *id)
#else
ConfigItemLogfile(id)
    char *id;
#endif
{
    CONDDEBUG((1, "ConfigItemLogfile(%s) [%s:%d]", id, file, line));

    if (parserConfigTemp->logfile != (char *)0)
	free(parserConfigTemp->logfile);

    if ((id == (char *)0) || (*id == '\000')) {
	parserConfigTemp->logfile = (char *)0;
	return;
    }
    if ((parserConfigTemp->logfile = StrDup(id)) == (char *)0)
	OutOfMem();
}
