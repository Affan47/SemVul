__sgferr(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp;
 char s1[RECLEN], s2[RECLEN];

 __pv_err_cnt++;
 if (!__no_errs)
  {
   if (__run_state == SS_SIM)
    sprintf(s1, " now %s", __to_timstr(s2, &__simtime));
   else strcpy(s1, "");

   if (__vpierr_cb_active && !__iact_state)
    {

     __errorcb_suppress_msg = FALSE;

     sprintf(vpis1, "**%s(%d) ERROR**%s [%d] ", __in_fils[__sfnam_ind],
      __slin_cnt, s1, id_num);
     va_start(va, s);
     vsprintf(vpis2, s, va);
     va_end(va);

     slen = strlen(vpis1) + strlen(vpis2) + 1;
     vpichp = __my_malloc(slen);
     strcpy(vpichp, vpis1);
     strcat(vpichp, vpis2);

     __cberror_fill_einfo(ERROR, id_num, vpichp, __in_fils[__sfnam_ind],
      __slin_cnt);
     __vpi_error_trycall();

     __my_free(vpichp, slen);

     if (__errorcb_suppress_msg)
      { __errorcb_suppress_msg = FALSE; return; }
    }

   __my_fprintf(stdout, "**%s(%d) ERROR**%s [%d] ", __in_fils[__sfnam_ind],
    __slin_cnt, s1, id_num);


   va_start(va2, s);
   va_start(va3, s);
   __my_vfprintf(stdout, s, va2, va3);
   va_end(va2);
   va_end(va3);
   my_putc_('\n', stdout);
  }
 if ((__run_state == SS_COMP || __run_state == SS_LOAD)
  && __max_errors != 0 && __pv_err_cnt > __max_errors)
  __pv_terr(id_num, "maximum error count exceeded");
}
