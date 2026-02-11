init_tok()
   {
   struct rsrvd_wrd *rw;
   static int first_time = 1;

   if (first_time) {
      first_time = 0;
      init_sbuf(&tknize_sbuf);


      for (rw = pp_rsrvd; rw->s != NULL; ++rw)
         rw->s = spec_str(rw->s);

      zero_tok = new_token(PpNumber, spec_str("0"), "", 0);
      one_tok = new_token(PpNumber, spec_str("1"), "", 0);
      }
   }
