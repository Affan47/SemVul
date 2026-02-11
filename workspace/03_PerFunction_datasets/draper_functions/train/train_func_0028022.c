ftgeti4 (entry, kw)

char	*entry;
struct Keyword *kw;
{
    char temp[30];

    if (ftgetc (entry, kw, temp, 30))
	return ( (int) atof (temp) );
    else
	return (0);
}
