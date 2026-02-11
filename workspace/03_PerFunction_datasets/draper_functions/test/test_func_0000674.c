__pv_ferr(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp;

 __pv_err_cnt++;
 if (__iact_state)
  {

   va_start(va, s);
   va_start(va2, s);
   __via_err(id_num, s, va, va2);
   va_end(va);
   va_end(va2);
   return;
  }

 if (!__no_errs)
  {
   if (__vpierr_cb_active)
    {

     __errorcb_suppress_msg = FALSE;

     sprintf(vpis1, "**%s(%d) ERROR** [%d] ", __cur_fnam, __lin_cnt, id_num);
     va_start(va, s);
     vsprintf(vpis2, s, va);
     va_end(va);

     slen = strlen(vpis1) + strlen(vpis2) + 1;
     vpichp = __my_malloc(slen);
     strcpy(vpichp, vpis1);
     strcat(vpichp, vpis2);

     __cberror_fill_einfo(ERROR, id_num, vpichp, __cur_fnam, __lin_cnt);
     __vpi_error_trycall();

     __my_free(vpichp, slen);

     if (__errorcb_suppress_msg)
      { __errorcb_suppress_msg = FALSE; return; }
    }
   __my_fprintf(stdout, "**%s(%d) ERROR** [%d] ", __cur_fnam, __lin_cnt,
    id_num);


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
