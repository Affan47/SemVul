gen_tcase(il, has_dflt)
struct il_code *il;
int has_dflt;
   {
   struct case_anlz case_anlz;


   findcases(il, has_dflt, &case_anlz);
   if (case_anlz.il_then == NULL) {
      if (case_anlz.il_else == NULL)
         return 1;
      else
         return gen_il(case_anlz.il_else);
      }
   else
      return gen_if(typ_chk(il->u[0].fld, case_anlz.typcd), case_anlz.il_then,
         case_anlz.il_else, sav_locs());
   }
