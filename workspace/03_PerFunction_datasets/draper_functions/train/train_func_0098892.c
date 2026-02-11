copyarcf(re, archre)
CONST reg_ex_t *re;
CONST char *archre;
{
	CONST char *cp;
	int i, j, n, len, parent;

	parent = (*archivedir) ? 0 : -1;

	for (i = 1; i < maxarcf; i++) {
		if (!(cp = skiparchdir(arcflist[i].name))) continue;
		if (!*cp) {
			parent = i;
			continue;
		}

		len = getarchdirlen(cp);
		if (len >= -1 && len <= 0) {
			if (parent <= 0) parent = i;
		}
		if (len < 0) continue;
		if (re && !regexp_exec(re, cp, 1)) continue;

		if (archre) {
			if (!(n = searcharcf(archre, arcflist, maxarcf, i)))
				continue;
			if (n < 0) break;
		}

		for (j = 0; j < stackdepth; j++)
			if (!strcmp(cp, filestack[j].name)) break;
		if (j < stackdepth) continue;

		filelist = addlist(filelist, maxfile, &maxent);
		memcpy((char *)&(filelist[maxfile]),
			(char *)&(arcflist[i]), sizeof(namelist));
		filelist[maxfile].name = (char *)cp;
#ifndef	NOSYMLINK
		filelist[maxfile].linkname = arcflist[i].linkname;
#endif
		maxfile++;
	}

	if (parent < 0) return;
	for (i = 0; i < maxfile; i++)
		if (isdotdir(filelist[i].name) == 1) return;
	filelist = addlist(filelist, maxfile, &maxent);
	memmove((char *)&(filelist[1]), (char *)&(filelist[0]),
		maxfile++ * sizeof(namelist));
	memcpy((char *)&(filelist[0]),
		(char *)&(arcflist[parent]), sizeof(namelist));
	filelist[0].name = arcflist[0].name;
#ifndef	NOSYMLINK
	filelist[0].linkname = NULL;
#endif
}
