infoassembly_updatereaddepth(const AjPCigar c,
                                          unsigned char* rdepth)
{
    ajint i=0;
    ajint length = 0;
    int j=0;

    for (i=0;i<c->n;i++)
    {
	switch (c->cigoperator[i])
	{
	    case 'M':
	    case 'D':
	    case 'N':
	    case '=':
	    case 'X':
		length += c->length[i];
		for(j=0; j<c->length[i]; j++)
		{
		    if(*rdepth != 0xff)
			(*rdepth++)++;
		    else
			rdepth++;
		}
	}
    }
    return length;
}
