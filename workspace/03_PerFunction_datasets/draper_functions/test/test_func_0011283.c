singlespace(char *p)
{
    char *pp, *p2;
    for(pp=p;*pp;pp++) {
	if(!isspace(*pp)) continue;
	if(leaveline) {
	    if(*pp==13) ovlstrcpy(pp,pp+1);
	    if(*pp=='\n') {
		pp++;
		gopt: for(p2=pp; isspace(*p2) && *p2!='\n'; p2++);
		if(p2>pp) ovlstrcpy(pp,p2); pp--;
	    }
	    else {
		pp++; if(!isspace(*pp) || *pp=='\n') continue;
		goto gopt;
	    }
	}
	else {
	    if(*pp!=' ') *pp=' ';
	    pp++; if(!isspace(*pp)) continue;
	    for(p2=pp;isspace(*p2);p2++);
	    ovlstrcpy(pp,p2); pp--;
	}
    }
}
