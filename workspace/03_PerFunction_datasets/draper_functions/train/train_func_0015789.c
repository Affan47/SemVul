GetSzOption (int scale, char *sz)
{
    char	*p;


    for (p = sz;  isdigit(*p); p++)
	continue;

    if (p == sz)
	return -1;
    else {
	switch (*p) {
	  case '\0':
	    break;
	  case 'k':
	  case 'K':
	    scale = ONE_K;
	    break;
	  case 'm':
	  case 'M':
	    scale = ONE_MEG;
	    break;
	  default:
	    return -1;
	}
	return (scale * atoi(sz));
    }

}
