ex_sc(p_sc)


p_sc_t p_sc;
{


 if (!tgindent && tglinmax==TGMAXINF)
   {
    wf_blk(&f_o, p_sc->sc_first, (size_t) (p_sc->sc_last-p_sc->sc_first+1));
    return;
   }


 {
  char *p      = p_sc->sc_first;
  char *p_post = p_sc->sc_last+1;
  while (TRUE)
    {
     char *p_sot = p;


     while (p!=p_post && *p!=EOL) p++;


     if (p>p_sot) {wf_blk(&f_o,p_sot,(size_t) (p-p_sot));ind_curr+=p-p_sot;}


     if (ind_curr>tglinmax && lineno!=errlin)
       {
        numlong++;
        if (numlong <= LONGMESS)
          {
           if (option.op_b7_b)
              sprintf(linet1,
                      "E: Product file line is too long (line %lu of \"%s\").",
                             (ulong) lineno,SUPPNAME);
           else
              sprintf(linet1,
                      "E: Product file line is too long (line %lu of \"%s\").",
                             (ulong) lineno,fn_targ);
           SENDLINE;
           if (numlong==1)
             {
              sprintf(linet1,"   Product file line length limit is %lu characters.",
                             (ulong) tglinmax);
              SENDLINE;
              sprintf(linet1,"   Note: You can change the limit by specifying.");
              SENDLINE;
              sprintf(linet1,"      @p maximum_output_line_length = <desired length>");
              SENDLINE;
              sprintf(linet1,"   somewhere in the input file.");
              SENDLINE;
             }
           errlin=lineno;
           num_err++;
          }
        if (numlong == LONGMESS+1)
          {
           sprintf(linet1,
           "Further line-too-long warnings for file \"%s\" have been suppressed.",
              fn_targ);
           SENDLINE;
          }
       }


     if (p==p_post) break;


     p++; lineno++;


     if (tgindent)
        eolblank(ind_base);
     else
        wf_chr(&f_o,EOL);
     ind_curr=ind_base;
    }
 }
}
