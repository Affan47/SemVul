check_parm(char *pm)
{
    char *p, *pp, *p2, buf[16];
    int i;

    for(p=pm;*p!=0;p++) {
	if(*p!='\\') continue;
	if(*(p+1)=='\n') *p=*(p+1)=' ';
	if(*(p+1)==0) *p=' ';
    }
    for(p=pm; *p!=0; p++) {
	if(!isalpha(*p)) continue;
	for(p2=p+1; isalpha(*p2); p2++);
	if(p2-p>10) {p=p2-1; continue;}
	memmove(buf,p,p2-p); buf[p2-p]=0; pp=p; p=p2-1;
	for(p2=buf; islower(*p2); p2++);
	if(*p2) continue;
	i=search_list(firstupper,firstupperno,sizeof(firstupper[0]),buf);
	if(i>=0) *pp=toupper(*pp);
    }
    find_illegal(pm);
}
