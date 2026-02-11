accessfile(char *content, char *type, char *s,...)
{
    va_list vp;
    char buf[MAX_LINELEN+1];
    FILE *f;
    int l;

    va_start(vp,s);
    vsnprintf(buf,sizeof(buf),s,vp);
    va_end(vp);
    f=fopen(buf,type); if(f==NULL) {
	if(*type=='r') content[0]=0; return;
    }
    switch(*type) {
	case 'a':
	case 'w': {
	    l=strlen(content); fwrite(content,1,l,f); break;
	}
	case 'r': {
	    l=fread(content,1,MAX_LINELEN-1,f);
	    if(l>0 && l<MAX_LINELEN) content[l]=0;
	    else content[0]=0;
	    break;
	}
	default: {
	    content[0]=0; break;
	}
    }
    fclose(f);
}
