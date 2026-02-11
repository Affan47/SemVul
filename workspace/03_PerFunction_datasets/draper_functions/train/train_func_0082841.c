output(char *p)
{
    int i,n;
    char *pp, *pe, *p1, *pt;
    char outbuf[MAX_LINELEN+1];

    pp=strstr(p,inprompt); if(pp==NULL) return;
    while(pp!=NULL && *pp!=0) {
	pp+=strlen(inprompt); p1=find_word_start(pp);
	pe=strstr(pp,outprompt);
	pt=strstr(pp,inprompt);
	if(pe==NULL || (pt!=NULL && pt<pe)) {
	    if(pt==NULL) pp=pp+strlen(pp); else pp=pt;
	    n=pp-p1; if(n>MAX_LINELEN) n=MAX_LINELEN; if(n<0) n=0;
	    memmove(outbuf,p1,n); outbuf[n]=0;
	    fprintf(stderr,"%s\n",outbuf);
	    puts(""); continue;
	}
	else {
	    *pe=0; pe=find_word_start(pe+strlen(outprompt));
	}
	pp=strstr(pe,inprompt);
	if(pp==NULL) pp=pe+strlen(pe);
	if(*p1==0) {
	    if(pp>=pe+sizeof(outbuf)) break;
	    n=pp-pe; if(n>MAX_LINELEN) n=MAX_LINELEN; if(n<0) n=0;
	    memmove(outbuf,pe,n); outbuf[n]=0;
	}
	else {
	    snprintf(outbuf,sizeof(outbuf),"%s",p1);
	    n=strlen(outbuf);
	}

	for(i=0;i<n;i++) {
	    if(outbuf[i]=='\n') outbuf[i]=' ';
	}

	for(i=n-1;i>=0 && isspace(outbuf[i]); i--) outbuf[i]=0;
	if(outbuf[i]==';') outbuf[i]=0;
	for(pe=outbuf; *pe; pe++) if(isupper(*pe)) *pe=tolower(*pe);
	for(pe=outbuf; isspace(*pe); pe++);

	puts(pe);
    }
}
