encode_whole_header(char *field, METAENV *header)
{
    int        retval = 0;
    PINEFIELD *pf;

    if(field && (!strucmp(field, "Subject") ||
		 !strucmp(field, "Comment") ||
		 !struncmp(field, "X-", 2)))
      retval++;
    else if(field && *field && header && header->custom){
	for(pf = header->custom; pf && pf->name; pf = pf->next){

	    if(!pf->standard && !strucmp(pf->name, field)){
		retval++;
		break;
	    }
	}
    }

    return(retval);
}
