iniparser_line(
    char * input_line,
    char * section,
    char * key,
    char * value)
{
    line_status sta ;
    char        line[ASCIILINESZ+1];
    int         len ;

    strcpy(line, strstrip(input_line));
    len = (int)strlen(line);

    sta = LINE_UNPROCESSED ;
    if (len<1) {

        sta = LINE_EMPTY ;
    } else if (line[0]=='#') {

        sta = LINE_COMMENT ;
    } else if (line[0]=='[' && line[len-1]==']') {

        sscanf(line, "[%[^]]", section);
        strcpy(section, strstrip(section));
        strcpy(section, strlwc(section));
        sta = LINE_SECTION ;
    } else if (sscanf (line, "%[^=] = \"%[^\"]\"", key, value) == 2
           ||  sscanf (line, "%[^=] = '%[^\']'",   key, value) == 2
           ||  sscanf (line, "%[^=] = %[^;#]",     key, value) == 2) {

        strcpy(key, strstrip(key));
        strcpy(key, strlwc(key));
        strcpy(value, strstrip(value));


        if (!strcmp(value, "\"\"") || (!strcmp(value, "''"))) {
            value[0]=0 ;
        }
        sta = LINE_VALUE ;
    } else if (sscanf(line, "%[^=] = %[;#]", key, value)==2
           ||  sscanf(line, "%[^=] %[=]", key, value) == 2) {


        strcpy(key, strstrip(key));
        strcpy(key, strlwc(key));
        value[0]=0 ;
        sta = LINE_VALUE ;
    } else {

        sta = LINE_ERROR ;
    }
    return sta ;
}
