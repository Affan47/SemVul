sigdash_strip(long int linenum, char *line, LT_INS_S **ins, void *local)
{
    if(*((int *)local)
       || (*line == '-' && *(line+1) == '-'
	   && *(line+2) == ' ' && !*(line+3))){
	*((int *) local) = 1;
	return(2);
    }

    return(0);
}
