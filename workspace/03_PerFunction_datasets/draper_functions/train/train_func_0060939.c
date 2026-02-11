include_comments (FILE *f, const char *comments)
{
    FILE *cf = NULL ;
    char buffer [MAXLINE] ;
    int ok = TRUE ;
    if (comments != NULL && comments [0] != '\0')
    {
	cf = fopen (comments, "r") ;
	if (cf == NULL)
	{
	    return (FALSE) ;
	}
	while (ok && fgets (buffer, MAXLINE, cf) != NULL)
	{

	    buffer [MMLEN-1] = '\0' ;
	    buffer [MMLEN-2] = '\n' ;
	    ok = ok && (fprintf (f, "%%%s", buffer) > 0) ;
	}
	fclose (cf) ;
    }
    return (ok) ;
}
