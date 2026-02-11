FindParserDefaultOrConsole(CONSENT *c, char *id)
#else
FindParserDefaultOrConsole(c, id)
    CONSENT *c;
    char *id;
#endif
{
    for (; c != (CONSENT *)0; c = c->pCEnext) {
	if (strcasecmp(id, c->server) == 0)
	    return c;
    }
    return c;
}
