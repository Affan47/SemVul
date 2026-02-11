parsing_warning(message, ptr, option)
char *message ;
char *ptr ;
char *option ;
{
    char *fname ;
    int lineno ;


    if (mf_locate(ptr, &fname, &lineno)) {
	fprintf(stderr, "%s:%d: ", fname, lineno) ;
    }


    fprintf(stderr, "%s parse warning: %s", stProgramName, message) ;
    if (option) {
	fprintf(stderr, " (%s)", option) ;
    }
    fprintf(stderr, "\n") ;
}
