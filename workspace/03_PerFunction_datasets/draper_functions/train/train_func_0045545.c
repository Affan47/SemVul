__tilde_fopen(char *pthnam, char *opmod)
{
 int32 newlen;
 char *chp;
 FILE *f;

 if (*pthnam != '~') return(__my_fopen(pthnam, opmod));
 if ((chp = tilde_expand(pthnam, &newlen)) == NULL) return(NULL);
 f = __my_fopen(chp, opmod);
 __my_free(chp, newlen);
 return(f);
}
