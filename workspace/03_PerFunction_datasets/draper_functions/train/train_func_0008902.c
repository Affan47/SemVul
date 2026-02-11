dollsub(p_comlin)


char *p_comlin;
{
 char *p=p_comlin;
 cl_t  cl;
 char *t;

 t = &cl[0];


 strcpy(t,p);


 while (*t != EOS)
   {

    if ((p-p_comlin) == COMLINE_MAX) goto toobig;


    if (*t!='$') {*p++ = *t++; continue;}


    t++;


    if (!isdigit(*t) && !isupper(*t) && *t!='$' && *t!='/')
      {
       wl_sj("S: Illegal dollar subtitution sequence in command line.");
       wl_sj("Legal sequences are $0..$9, $A..$Z, $/, and $$.");
       num_sev++;
       strcpy(p,t);
       return;
      }


    if (*t=='$') {*p++ = *t++; continue;}


    if (*t=='/') {*p++ = FN_DELIM; t++; continue;}


    if (isdigit(*t) || isupper(*t))
      {
       ubyte num;
       char *q;
       if (isdigit(*t))
           num = *t-'0';
       else
           num = 10+(*t-'A');
       as_cold(num<NUM_SUBS,"dollsub: num is too bug!");
       q=subval[num];
       if ((p-p_comlin)+strlen(subval[num]) > COMLINE_MAX) goto toobig;
       while (*q!=EOS) *p++ = *q++;
       t++;
      }
   }
 *p=EOS;
 return;

 toobig:
    wl_sj("S: Expanded (i.e. after $1 etc) command line is too long.");
    num_sev++;
    strcpy(p,t);
    return;
}
