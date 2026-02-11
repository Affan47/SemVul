vhost_xref(char *p)
{
    char *space;
    size_t offset;
    char *field = NULL;

    space = strchr(p, ' ');
    if (space == NULL) {
	warn("malformed Xref: `%s'", field);
	goto fail;
    }
    offset = space - p;
    space = strchr(p + offset, ' ');
    if (space == NULL) {
	warn("malformed Xref: `%s'", field);
	goto fail;
    }
    field = concat(PERMaccessconf->domain, space, NULL);
 fail:
    free(p);
    return field;
}
