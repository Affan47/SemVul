parseOFLibDate(char *str) {
    char *end;
    int days, hours, min, i;


    while ( isspace(*str)) ++str;
    days = 0;
    for ( i=0; i<12; ++i ) {
	if ( strncmp(str,monnames[i],strlen(monnames[i]))==0 )
    break;
	days += fakemons[i];
    }
    if ( i!=12 )
	str += strlen(monnames[i]);
    while ( isspace(*str)) ++str;
    days += strtol(str,&end,10)-1;

    str = end;
    while ( *str==',' || isspace(*str)) ++str;
    days += 366 * (strtol(str,&end,10)-2005);

    str = end;
    while ( isspace(*str)) ++str;
    hours = strtol(str,&end,10);
    if ( hours==12 ) hours=0;
    str = end;
    if ( *str==':' ) ++str;
    min = strtol(str,&end,10);
    str = end;

    while ( isspace(*str)) ++str;
    if ( strncmp(str,"pm",2)==0 )
	hours += 12;
return( days*24*60 + hours*60 + min );
}
