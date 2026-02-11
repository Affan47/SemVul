set_refspecs(const char **refs, int nr)
{
	int i;
	for (i = 0; i < nr; i++) {
		const char *ref = refs[i];
		if (!strcmp("tag", ref)) {
			char *tag;
			int len;
			if (nr <= ++i)
				die("tag shorthand without <tag>");
			len = strlen(refs[i]) + 11;
			if (deleterefs) {
				tag = xmalloc(len+1);
				strcpy(tag, ":refs/tags/");
			} else {
				tag = xmalloc(len);
				strcpy(tag, "refs/tags/");
			}
			strcat(tag, refs[i]);
			ref = tag;
		} else if (deleterefs && !strchr(ref, ':')) {
			char *delref;
			int len = strlen(ref)+1;
			delref = xmalloc(len+1);
			strcpy(delref, ":");
			strcat(delref, ref);
			ref = delref;
		} else if (deleterefs)
			die("--delete only accepts plain target ref names");
		add_refspec(ref);
	}
}
