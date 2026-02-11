prepare_dic(void)
{
    int i;
    FILE *dicf;
    char *p1, *p2, *pp;
    long int flen;

    entrycount=0;
    dicf=fopen(dicname,"r"); if(dicf==NULL) return;
    fseek(dicf,0,SEEK_END);flen=ftell(dicf); fseek(dicf,0,SEEK_SET);
    if(flen>diclim) return;
    dicbuf=xmalloc(2*flen+1024);flen=fread(dicbuf,1,flen,dicf);
    fclose(dicf);
    if(flen>0 && flen<diclim) dicbuf[flen]=0;
    else return;
    for(i=0,p1=dicbuf;p1!=NULL && *p1!=0 && i<entrylim;p1=p2) {
	p2=strchr(p1+1,'\n'); if(p2>p1) *p2++=0;
	pp=strchr(p1,sepchar); if(pp==NULL) continue;
	*pp++=0;
	strip_trailing_spaces(p1); strip_trailing_spaces(pp);
	singlespace(p1);
	p1=find_word_start(p1); pp=find_word_start(pp);
	if(*p1==0) continue;
	entry[i].original=p1; entry[i].replace=pp; i++;
    }
    entrycount=i;
}
