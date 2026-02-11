find_io_keyword(char *s)

#else
find_io_keyword(s)
     char *s;
#endif
{
    int i;
    for(i=0; io_keywords[i].name != NULL; i++) {
	if(strcmp(io_keywords[i].name, s) == 0) {
	    break;
	}
    }
    return i;
}
