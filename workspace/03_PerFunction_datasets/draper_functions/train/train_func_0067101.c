sspm_is_blank(char* line)
{
    char *p;
    char c =0;

    for(p=line; *p!=0; p++){
	if( ! (*p == ' '|| *p == '\t' || *p=='\n') ){
	    c++;
	}
    }

    if (c==0){
	return 1;
    }

    return 0;

}
