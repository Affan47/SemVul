modemstate(const char* arg)
{
    static struct {
	const char* tag;
	const char* state;
    } modemstates[] = {
	{ "busy",  "B" },
	{ "ready", "R" }, { "up",      "R" },
	{ "down",  "D" }, { "disable", "D" },
	{ NULL }
    };
    int i;

    for (i = 0; modemstates[i].tag != NULL; i++)
	if (strcmp(modemstates[i].tag, arg) == 0)
	    return (modemstates[i].state);
    fatal("Bad modem ready state `%s'; use one of busy, ready, and down", arg);

    return (NULL);
}
