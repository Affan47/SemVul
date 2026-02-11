do_permonst()
{
	int	i;
	char	*c, *nam;

	filename[0]='\0';
#ifdef FILE_PREFIX
	Strcat(filename, file_prefix);
#endif
	Sprintf(eos(filename), INCLUDE_TEMPLATE, MONST_FILE);
	if (!(ofp = fopen(filename, WRTMODE))) {
		perror(filename);
		exit(EXIT_FAILURE);
	}
	Fprintf(ofp,"/*\tSCCS Id: @(#)pm.h\t3.4\t2002/02/03 */\n\n");
	Fprintf(ofp,Dont_Edit_Code);
	Fprintf(ofp,"#ifndef PM_H\n#define PM_H\n");

	if (strcmp(mons[0].mname, "playermon") != 0)
		Fprintf(ofp,"\n#define\tPM_PLAYERMON\t(-1)");

	for (i = 0; mons[i].mlet; i++) {
		SpinCursor(3);

		Fprintf(ofp,"\n#define\tPM_");
		if (mons[i].mlet == S_HUMAN &&
				!strncmp(mons[i].mname, "were", 4))
		    Fprintf(ofp, "HUMAN_");
		for (nam = c = tmpdup(mons[i].mname); *c; c++)
		    if (*c >= 'a' && *c <= 'z') *c -= (char)('a' - 'A');
		    else if (*c < 'A' || *c > 'Z') *c = '_';
		Fprintf(ofp,"%s\t%d", nam, i);
	}
	Fprintf(ofp,"\n\n#define\tNUMMONS\t%d\n", i);
	Fprintf(ofp,"\n#endif /* PM_H */\n");
	Fclose(ofp);
	return;
}
