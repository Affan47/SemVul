check_malloc(size)
unsigned size ;
{
    char *tmp ;

    tmp = malloc(size) ;
    if (tmp == NULL) {
	fatal(NOMORECORE, NULL) ;
    }
    return tmp ;
}
