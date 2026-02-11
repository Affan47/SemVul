skipcomma(char *pt) {
    while ( isspace(*pt))++pt;
    if ( *pt==',' ) ++pt;
return( pt );
}
