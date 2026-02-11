GResourceFindInt(char *name, long def) {
    int pos;
    char *end;
    long ret;

    pos = _GResource_FindResName(name);
    if ( pos==-1 )
return( def );

    ret = strtol(_GResource_Res[pos].val,&end,10);
    if ( *end!='\0' )
return( def );

return( ret );
}
