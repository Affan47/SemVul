compile_fs_type(char *fs_type, struct fs_type_compile *cmp)
{
	char 	*cp, *list, *s;
	int	num = 2;
	int	negate, first_negate = 1;

	if (fs_type) {
		for (cp=fs_type; *cp; cp++) {
			if (*cp == ',')
				num++;
		}
	}

	cmp->list = malloc(num * sizeof(char *));
	cmp->type = malloc(num * sizeof(int));
	if (!cmp->list || !cmp->type) {
		fputs(_("Couldn't allocate memory for filesystem types\n"),
		      stderr);
		exit(EXIT_ERROR);
	}
	memset(cmp->list, 0, num * sizeof(char *));
	memset(cmp->type, 0, num * sizeof(int));
	cmp->negate = 0;

	if (!fs_type)
		return;

	list = string_copy(fs_type);
	num = 0;
	s = strtok(list, ",");
	while(s) {
		negate = 0;
		if (strncmp(s, "no", 2) == 0) {
			s += 2;
			negate = 1;
		} else if (*s == '!') {
			s++;
			negate = 1;
		}
		if (strcmp(s, "loop") == 0)

			goto loop_special_case;
		else if (strncmp(s, "opts=", 5) == 0) {
			s += 5;
		loop_special_case:
			cmp->type[num] = negate ? FS_TYPE_NEGOPT : FS_TYPE_OPT;
		} else {
			if (first_negate) {
				cmp->negate = negate;
				first_negate = 0;
			}
			if ((negate && !cmp->negate) ||
			    (!negate && cmp->negate)) {
				fputs(_(fs_type_syntax_error), stderr);
				exit(EXIT_USAGE);
			}
		}
#if 0
		printf("Adding %s to list (type %d).\n", s, cmp->type[num]);
#endif
	        cmp->list[num++] = string_copy(s);
		s = strtok(NULL, ",");
	}
	free(list);
}
