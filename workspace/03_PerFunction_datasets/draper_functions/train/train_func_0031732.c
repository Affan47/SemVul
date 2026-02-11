mk_atom(scheme *sc, char *q) {
     char    c, *p;
     int has_dec_point=0;
     int has_fp_exp = 0;

#if USE_COLON_HOOK
     if((p=strstr(q,"::"))!=0) {
          *p=0;
          return cons(sc, sc->COLON_HOOK,
                          cons(sc,
                              cons(sc,
                                   sc->QUOTE,
                                   cons(sc, mk_atom(sc,p+2), sc->NIL)),
                              cons(sc, mk_symbol(sc,strlwr(q)), sc->NIL)));
     }
#endif

     p = q;
     c = *p++;
     if ((c == '+') || (c == '-')) {
       c = *p++;
       if (c == '.') {
         has_dec_point=1;
	 c = *p++;
       }
       if (!isdigit((int) c)) {
	 return (mk_symbol(sc, strlwr(q)));
       }
     } else if (c == '.') {
       has_dec_point=1;
       c = *p++;
       if (!isdigit((int) c)) {
	 return (mk_symbol(sc, strlwr(q)));
       }
     } else if (!isdigit((int) c)) {
       return (mk_symbol(sc, strlwr(q)));
     }

     for ( ; (c = *p) != 0; ++p) {
          if (!isdigit((int) c)) {
               if(c=='.') {
                    if(!has_dec_point) {
                         has_dec_point=1;
                         continue;
                    }
               }
               else if ((c == 'e') || (c == 'E')) {
                       if(!has_fp_exp) {
                          has_dec_point = 1;

                          p++;
                          if ((*p == '-') || (*p == '+') || isdigit((int) *p)) {
                             continue;
                          }
                       }
               }
               return (mk_symbol(sc, strlwr(q)));
          }
     }
     if(has_dec_point) {
          return mk_real(sc,atof(q));
     }
     return (mk_integer(sc, atol(q)));
}
