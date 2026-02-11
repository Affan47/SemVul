getFlagsFromString(char *string, const MaskString array[], int elements)
{
    unsigned long ret = 0;
    short i = 0;
    char *cp;
    char *buf;
    char *end;

    if(!string || !string[0]) {
	return ret;
    }


    buf = PR_Malloc(strlen(string)+1);
    if(!buf) {
	out_of_memory();
    }
    strcpy(buf, string);


    for(cp=buf; cp && *cp; cp = (end ? end+1 : NULL) ) {

	end = strchr(cp, ':');
	if(end) {
	    *end = '\0';
	}


	for(i=0; i < elements; i++) {
	    if( !PORT_Strcasecmp(cp, array[i].name) ) {
		break;
	    }
	}
	if(i == elements) {

	    PR_fprintf(PR_STDERR, errStrings[INVALID_CONSTANT_ERR], cp);
	    continue;
	}
	ret |= array[i].mask;
    }

    PR_Free(buf);
    return ret;
}
