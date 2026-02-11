post(int fd, int result, const char *virname, void *context)
{
    struct metachain *c = context;
    if (c && c->n) {
	char str[128];
	int toolong = print_chain(c, str, sizeof(str));
	if (c->level == c->lastadd && !virname)
	    free(c->chains[--c->n]);
	if (virname && !c->lastvir)
	    c->lastvir = c->level;
    }
    if (c)
	c->level--;
    return CL_CLEAN;
}
