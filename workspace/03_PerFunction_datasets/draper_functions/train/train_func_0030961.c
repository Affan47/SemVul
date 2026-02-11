parseinalias(const char *filename,int linenr,char *buffer) {
	char *value = extractvalue(buffer);
	struct windowmanager *wm;

	if( value == NULL ) {
		fprintf(stderr,"%s:%d: Missing = sign!\n",filename,linenr);


		exit(EXIT_FAILURE);
	}

	wm = findwm(value);
	if( wm == NULL ) {
		fprintf(stderr,"%s:%d: Could not find '%s', not yet defined?\n",filename,linenr,value);
	} else {
		struct inalias *alias;

		alias = xmalloc(sizeof(struct inalias));
		alias->next = aliases;
		aliases = alias;
		alias->toreplace = xstrdup(buffer);
		alias->with = wm;
		alias->forceask = FALSE;
	}
}
