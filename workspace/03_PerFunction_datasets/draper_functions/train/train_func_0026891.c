toLower(Expr_t * pgm, char *s, Sfio_t* tmps)
{
    int c;

    while ((c = *s++))
	sfputc (tmps, tolower (c));

    return exstring(pgm, sfstruse(tmps));
}
