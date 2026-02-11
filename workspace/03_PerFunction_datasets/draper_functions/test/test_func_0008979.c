ichartostr (out, in, outlen, canonical)
    register unsigned char *
			out;
    register const ichar_t *
			in;
    int			outlen;
    int			canonical;
    {
    register unsigned int
			ch;
    register int	i;
    register unsigned char *
			scharp;

    while (--outlen > 0  &&  (ch = *in++) != '\0')
	{
	if (ch < SET_SIZE)
	    *out++ = (char) ch;
	else
	    {
	    ch -= SET_SIZE;
	    if (!canonical)
		{
		for (i = hashheader.nstrchars;  --i >= 0;  )
		    {
		    if (hashheader.groupnos[i] == defstringgroup
		      &&  hashheader.stringdups[i] == ch)
			{
			ch = i;
			break;
			}
		    }
		}
	    scharp = hashheader.stringchars[(unsigned) ch];
	    while ((*out++ = *scharp++) != '\0')
		;
	    out--;
	    }
	}
    *out = '\0';
    return outlen <= 0;
    }
