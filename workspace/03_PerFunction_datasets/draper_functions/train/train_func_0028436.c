invfind(INVCONTROL *invcntl, char *searchterm)
{
	int	imid, ilow, ihigh;
	long	num;
	int	i;
	unsigned long	*intptr, *intptr2;
	ENTRY *entryptr;


	if (invcntl->invfile == 0)
		return(-1L);


	intptr = (unsigned long *)invcntl->iindex;

	ilow = 0;
	ihigh = *intptr++ - 1;
	while (ilow <= ihigh) {
		imid = (ilow + ihigh) / 2;
		intptr2 = intptr + imid;
		i = strcmp(searchterm, (invcntl->iindex + *intptr2));
		if (i < 0)
			ihigh = imid - 1;
		else if (i > 0)
			ilow = ++imid;
		else {
			ilow = imid + 1;
			break;
		}
	}

	imid = (ilow) ? ilow - 1 : 0;


	if ((imid != invcntl->numblk) || (invcntl->param.filestat >= INVBUSY)) {
		fseek(invcntl->invfile,
		      (imid*invcntl->param.sizeblk) + invcntl->param.cntlsize,
		      SEEK_SET);
		invcntl->numblk = imid;
		fread(invcntl->logblk, (int)invcntl->param.sizeblk, 1,
		      invcntl->invfile);
	}

srch_ext:

	intptr = (unsigned long *) invcntl->logblk->invblk;

	ilow = 0;
	ihigh = *intptr - 1;
	intptr += 3;
	num = 0;
	while (ilow <= ihigh) {
		imid = (ilow + ihigh) / 2;
		entryptr = (ENTRY *)intptr + imid;
		i = strncmp(searchterm, invcntl->logblk->chrblk + entryptr->offset,
		    (int) entryptr->size );
		if (i == 0)
			i = strlen(searchterm) - entryptr->size;
		if (i < 0)
			ihigh = imid - 1;
		else if (i > 0)
			ilow = ++imid;
		else {
			num = entryptr->post;
			break;
		}
	}

	if (imid >= invcntl->logblk->invblk[0]) {
		invcntl->keypnt = invcntl->logblk->invblk[0];
		invstep(invcntl);

		if (invcntl->param.startbyte < invcntl->numblk * invcntl->param.sizeblk)
			goto srch_ext;
	} else
		invcntl->keypnt = imid;
	return(num);
}
