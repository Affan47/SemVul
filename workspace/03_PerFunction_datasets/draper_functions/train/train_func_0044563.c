ProcessProtocol(CONSENT *c, char *id)
#else
ProcessProtocol(c, id)
    CONSENT *c;
    char *id;
#endif
{
    if ((id == (char *)0) || (*id == '\000')) {
	c->raw = FLAGUNKNOWN;
	return;
    }

    if (strcmp(id, "telnet") == 0) {
	c->raw = FLAGFALSE;
	return;
    }
    if (strcmp(id, "raw") == 0) {
	c->raw = FLAGTRUE;
	return;
    }
    if (isMaster)
	Error("invalid protocol name `%s' [%s:%d]", id, file, line);
}
