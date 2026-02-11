is_boundary(struct mimestack *s, const char *line,
				     int *isclosing)
{
	struct mimestack *b;

	if (line[0] != '-' || line[1] != '-' ||
	    (b=libmail_mimestack_search(s, line+2)) == 0)
		return (NULL);


	*isclosing=strncmp(line+2+strlen(b->boundary), "--", 2) == 0;
	return (b);
}
