filter_check_pass(const char * word, unsigned int cond)
{
 int i = 0;
 int sl_ret = 0;
 int cl_ret = 0;
 int nb_ret = 0;
 int ss_ret = 0;

#ifdef APG_DEBUG
 fprintf (stdout, "DEBUG> filter_check_pass: ck pass: %s\n", word);
 fflush (stdout);
#endif

 if ((cond & S_SS) > 0)
    for (i=0; i < 94; i++)
       if ((smbl[i].type & S_SS) > 0)
          if ((strchr(word,smbl[i].ch)) != NULL)
	     ss_ret = 1;
 i = 0;
 if ((cond & S_SL) > 0)
    for (i=0; i < 94; i++)
       if ((smbl[i].type & S_SL) > 0)
          if ((strchr(word,smbl[i].ch)) != NULL)
	     sl_ret = 1;
 i = 0;
 if ((cond & S_CL) > 0)
    for (i=0; i < 94; i++)
       if ((smbl[i].type & S_CL) > 0)
          if ((strchr(word,smbl[i].ch)) != NULL)
	     cl_ret = 1;
 i = 0;
 if ((cond & S_NB) > 0)
    for (i=0; i < 94; i++)
       if ((smbl[i].type & S_NB) > 0)
          if ((strchr(word,smbl[i].ch)) != NULL)
	     nb_ret = 1;
 if (((cond & S_SS) > 0) &&(ss_ret != 1)) return (1);
 if (((cond & S_SL) > 0) &&(sl_ret != 1)) return (1);
 if (((cond & S_CL) > 0) &&(cl_ret != 1)) return (1);
 if (((cond & S_NB) > 0) &&(nb_ret != 1)) return (1);

#ifdef APG_DEBUG
 fprintf (stdout, "DEBUG> filter_check_pass: password %s pass the filter\n", word);
 fflush (stdout);
#endif
 return(0);
}
