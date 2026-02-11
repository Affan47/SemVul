get_name(linep)
char **linep ;
{
    char *name_beg ;
    char *name_end ;

    name_beg = skip_over_whitespace(*linep) ;
    name_end = skip_over_name(name_beg) ;

    if (name_beg == name_end) {
	parsing_error("name or macro expected", *linep, NULL) ;
    }

    *linep = name_end ;
    return unquote(check_strndup(name_beg, name_end - name_beg)) ;
}
