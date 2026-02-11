runfile(hdr, num, arg)
	struct heads   *hdr;
	int             num;
	char           *arg[];
{
	FILE           *tmp, *fopen();
	char            buf[STRLEN], *makefnam();
#if	DOS
	char		nbuf[64], *i, *rindex();
#endif
#if	!GEMDOS
	int             n;
	char            sys[STRLEN];
#endif


#if	UNIX
	sprintf(buf, "%s.RUN", arctemp);
	strcpy(sys, buf);
#else
	strcpy(nbuf, arctemp);
	makefnam(nbuf,hdr->name,buf);
	i = rindex(buf,'.');
#endif
#if	MSDOS
	if (!strcmp(i, ".BAS")) {
		strcpy(sys, "BASICA ");
		strcat(sys, buf);
	}
	else if (!strcmp(i, ".BAT")
		 || !strcmp(i, ".COM")
		 || !strcmp(i, ".EXE"))
		strcpy(sys, buf);

	else {
		if (warn) {
			printf("File %s is not a .BAS, .BAT, .COM, or .EXE\n",
			       hdr->name);
			nerrs++;
		}
		fseek(arc, hdr->size, 1);
		return;
	}
#endif
#if	GEMDOS
      if (strcmp(i, ".PRG")
              && strcmp(i, ".TTP")
              && strcmp(i, ".TOS"))
      {
              if (warn) {
                      printf("File %s is not a .PRG, .TOS, or .TTP\n",
                              hdr->name);
                      nerrs++;
              }
              fseek(arc, hdr->size, 1);
              return;
      }
#endif

	if (warn)
		if ((tmp = fopen(buf, "r")))
			arcdie("Temporary file %s already exists", buf);
	if (!(tmp = tmpopen(buf)))
		arcdie("Unable to create temporary file %s", buf);

	if (note)
		printf("Invoking file: %s\n", hdr->name);

	unpack(arc, tmp, hdr);
	fclose(tmp);
#if UNIX
	chmod(buf, 0700);
#endif
#if	GEMDOS
	execve(buf, arg, NULL);
#else
	for (n = 1; n < num; n++) {
		strcat(sys, " ");
		strcat(sys, arg[n]);
	}
	if (system(buf))
		arcdie("Execution failed for %s", buf);
#endif
	if (unlink(buf) && warn) {
		printf("Cannot unsave temporary file %s\n", buf);
		nerrs++;
	}
}
