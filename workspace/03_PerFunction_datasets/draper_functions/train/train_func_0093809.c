searchvar (char *name)


{	int r;
	header *hd=(header *)startlocal;
	r=xor(name);
	while ((char *)hd<endlocal)
	{	if (r==hd->xor && !strcmp(hd->name,name)) return hd;
		hd=nextof(hd);
	}
	if (startglobal!=startlocal && searchglobal)
	{   hd=(header *)startglobal;
		while ((char *)hd<endglobal)
		{	if (r==hd->xor && !strcmp(hd->name,name)) return hd;
			hd=nextof(hd);
		}
	}
	return 0;
}
