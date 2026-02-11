ajGraphicsBasecolourNewNuc(const AjPStr codes)
{
    ajint *ret;
    const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ajint colours[] =
        {
	GREEN,YELLOW,BLUE,YELLOW,YELLOW,YELLOW,
	BLACK,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,
	YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,
	YELLOW,RED,RED,YELLOW,YELLOW,YELLOW,
	YELLOW,YELLOW,YELLOW
    };
    const char* cp;
    const char* cq;
    ajint i;
    ajint j;

    ret = (ajint *) AJALLOC0(sizeof(ajint)*AZ);

    ajDebug("ajGraphGetBaseColourProt '%S'\n", codes);

    cp = ajStrGetPtr(codes);
    i = 1;

    while(*cp)
    {
	cq = strchr(alphabet, *cp);

	if(cq)
	{
	    j = cq - alphabet;
	    ret[i] = colours[j];
	    ajDebug("ColourProt %d: '%c' %d -> %d %s\n",
		    i, *cp, j, colours[j], graphColourName[colours[j]]);
	}

	i++;
	cp++;
    }

    return ret;
}
