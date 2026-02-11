cm_cvt(char *val, void *def) {
    static char *choices[] = { "default", "current", "copy", "private", NULL };
    int ret = match(choices,val);
    if ( ret== -1 )
return( (void *) -1 );

return( (void *) (intpt) (ret-1) );
}
