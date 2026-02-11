check_parm(char *pm)
{
    char *s, *pp;
    int l;

    for(pp=strchr(pm,'_'); pp!=NULL; pp=strchr(pp+1,'_')) *pp='K';

    if(strchr(pm,'?')!=NULL) {
	  fprintf(stderr,"Illegal under WIMS.\n"); exit(1);
    }
    for(s=pm;*s;s++) *s=tolower(*s);
    strip_trailing_spaces(pm); l=strlen(pm);
    if(l>0 && pm[l-1]!=';') strcat(pm,";");
    find_illegal(pm);
}
