escapedString (const char*src)
{
    char* res;
    int len;
    len = strlen(src);
    res = (char*)malloc(len+1);
    if (res)
    {
	char* dst = res;
	for (int i = 0; i <= len; i++)
	{
	    switch (src[i])
	    {
	    	case '\\':
		    switch (src[++i])
		    {
			case 'n':	*dst++ = '\n';	break;
			case 'r':	*dst++ = '\r';	break;
			case 't':	*dst++ = '\t';	break;
			default:
			    *dst++ = src[i];
		    }
		    break;
		case '%':
		    *dst++ = src[i];
		    switch (src[++i])
		    {
			case 'n':	*dst++ = '%';	break;
			default:
			    *dst++ = src[i];
		    }
		    break;

		default:
		    *dst++ = src[i];
	    }
	}
    } else
    {
    	exit(ENOMEM);
    }
    return res;
}
