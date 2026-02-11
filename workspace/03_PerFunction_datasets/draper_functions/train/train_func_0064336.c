_getdef(char buf[], char *name, char value[])
{
    char *p1, *p2, *p3, *p4;

    if(*name==0) goto nothing;
    for(p1=strstr(buf,name); p1!=NULL; p1=strstr(p1+1,name)) {
	p2=find_word_start(p1+strlen(name));
	if((p1>buf && !isspace(*(p1-1))) || *p2!='=') continue;
	p3=p1; while(p3>buf && *(p3-1)!='\n') p3--;
	p3=find_word_start(p3);
	if(p3<p1 && *p3!='!') continue;
	if(p3<p1) {
	    p3++; p4=find_word_end(p3);
	    if(find_word_start(p4)!=p1) continue;
	    if(p4-p3!=3 || (strncmp(p3,"set",3)!=0 &&
	       strncmp(p3,"let",3)!=0 &&
	       strncmp(p3,"def",3)!=0)) {
		if(p4-p3!=6 || strncmp(p3,"define",6)!=0) continue;
	    }
	}
	p2++;p3=strchr(p2,'\n'); if(p3==NULL) p3=p2+strlen(p2);
	p2=find_word_start(p2);
	if(p2>p3) goto nothing;
	if(p3-p2>=MAX_LINELEN) error("string_too_long def %s",name);
	memmove(value,p2,p3-p2); value[p3-p2]=0;
	strip_trailing_spaces(value); return;
    }
nothing:
    value[0]=0; return;
}
