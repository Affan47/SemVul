isnum(char *s)
{
    char       *cp;
    int         rval = FALSE;


    cp = s;
    (void) strtod(s, &cp);
    if ((*cp == '\0') && (cp != s))
        rval = TRUE;


    else
      {
          cp = s;
          (void) strtol(s, &cp, 0);
          if ((*cp == '\0') && (cp != s))
              rval = TRUE;
      }

    return (rval);
}
