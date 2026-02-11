parseit(char *in, int *n, char *out[])
{
    int instring = 0;
    int found = 0;
    int i;


    while(*in != '\0') {

	if(isspace(*in)) {
	    in++;
	    continue;
	}

	if(*in == ';') {
	    *in = '\0';
	    in++;
	    break;
	}

	if(*in == ',') {
	    *in = '\0';

	    if(!instring) {
		if(++found > *n) {
		    while(*in && *in != ';')
			in++;
		    if(*in)
			in++;
		    found--;
		    break;
		}

		*out = in;
		out++;
	    }

	    instring = 0;
	    in++;
	    continue;
	}

	if(!instring) {
	    if(++found > *n) {
		while(*in && *in != ';')
		    in++;
		if(*in)
		    in++;
		found--;
		break;
	    }

	    *out = in;
	    out++;
	    instring++;
	}

	in++;
    }

    for(i = found; i < *n; i++)
	*out++ = NULL;

    *n = found;

    return in;
}
