icalparser_get_prop_name(char* line, char** end)
{
    char* p;
    char* v;
    char *str;

    p = icalparser_get_next_char(';',line);
    v = icalparser_get_next_char(':',line);
    if (p== 0 && v == 0) {
	return 0;
    }


    if (v!=0 && ( p == 0 || p > v)){
	str = make_segment(line,v);
	*end = v+1;
    } else {
	str = make_segment(line,p);
	*end = p+1;
    }

    return str;
}
