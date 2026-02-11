initial_to_keyword(char *initial)
{
    KEYWORD_S *kw;
    char      *ret;
    int        init;
    int        kwinit;

    ret = initial;
    if(initial[0] && initial[1] == '\0'){
	init = initial[0];
	if(isascii(init) && isupper(init))
	  init = tolower((unsigned char) init);

	for(kw = ps_global->keywords; kw; kw = kw->next){
	    if(kw->nick)
	      kwinit = kw->nick[0];
	    else if(kw->kw)
	      kwinit = kw->kw[0];

	    if(isascii(kwinit) && isupper(kwinit))
	      kwinit = tolower((unsigned char) kwinit);

	    if(kwinit == init){
		ret = kw->kw;
		break;
	    }
	}
    }

    return(ret);
}
