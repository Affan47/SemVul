ProcessYesNo(char *id, FLAG *flag)
#else
ProcessYesNo(id, flag)
    char *id;
    FLAG *flag;
#endif
{
    if (id == (char *)0 || id[0] == '\000')
	*flag = FLAGFALSE;
    else if (strcasecmp("yes", id) == 0 || strcasecmp("true", id) == 0 ||
	     strcasecmp("on", id) == 0)
	*flag = FLAGTRUE;
    else if (strcasecmp("no", id) == 0 || strcasecmp("false", id) == 0 ||
	     strcasecmp("off", id) == 0)
	*flag = FLAGFALSE;
}
