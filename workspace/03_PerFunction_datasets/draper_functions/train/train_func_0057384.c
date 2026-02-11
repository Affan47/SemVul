importvar(char *name0, char *value) {
	char sep[2] = { ENV_SEPARATOR, '\0' };

	Ref(char *, name, name0);
	Ref(List *, defn, NULL);
	defn = fsplit(sep, mklist(mkstr(value + 1), NULL), FALSE);

	if (strchr(value, ENV_ESCAPE) != NULL) {
		List *list;
		gcdisable();
		for (list = defn; list != NULL; list = list->next) {
			int offset = 0;
			const char *word = list->term->str;
			const char *escape;
			while ((escape = strchr(word + offset, ENV_ESCAPE))
			       != NULL) {
				offset = escape - word + 1;
				switch (escape[1]) {
				    case '\0':
					if (list->next != NULL) {
						const char *str2
						  = list->next->term->str;
						char *str
						  = gcalloc(offset
							    + strlen(str2) + 1,
							    &StringTag);
						memcpy(str, word, offset - 1);
						str[offset - 1]
						  = ENV_SEPARATOR;
						strcpy(str + offset, str2);
						list->term->str = str;
						list->next = list->next->next;
					}
					break;
				    case ENV_ESCAPE: {
					char *str
					  = gcalloc(strlen(word), &StringTag);
					memcpy(str, word, offset);
					strcpy(str + offset, escape + 2);
					list->term->str = str;
					offset += 1;
					break;
				    }
				}
			}
		}
		gcenable();
	}
	vardef(name, NULL, defn);
	RefEnd2(defn, name);
}
