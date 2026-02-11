put_ilc(db, ilc)
FILE *db;
struct il_c *ilc;
   {


   if (ilc == NULL) {
      fprintf(db, "nil ");
      return;
      }
   fprintf(db, "$c ");
   while (ilc != NULL) {
      switch(ilc->il_c_type) {
         case ILC_Ref:
            put_var(db, 'r', ilc);
            break;
         case ILC_Mod:
            put_var(db, 'm', ilc);
            break;
         case ILC_Tend:
            put_var(db, 't', ilc);
            break;
         case ILC_SBuf:
            fprintf(db, "$sb ");
            break;
         case ILC_CBuf:
            fprintf(db, "$cb ");
            break;
         case ILC_Ret:
            fprintf(db, "$ret ");
            put_ret(db, ilc);
            break;
         case ILC_Susp:
            fprintf(db, "$susp ");
            put_ret(db, ilc);
            break;
         case ILC_Fail:
            fprintf(db, "$fail ");
            break;
         case ILC_EFail:
            fprintf(db, "$efail ");
            break;
         case ILC_Goto:
            fprintf(db, "$goto %d ", ilc->n);
            break;
         case ILC_CGto:
            fprintf(db, "$cgoto ");
            put_ilc(db, ilc->code[0]);
            fprintf(db, "%d ", ilc->n);
            break;
         case ILC_Lbl:
            fprintf(db, "$lbl %d ", ilc->n);
            break;
         case ILC_LBrc:
            fprintf(db, "${ ");
            break;
         case ILC_RBrc:
            fprintf(db, "$} ");
            break;
         case ILC_Str:
            fprintf(db, "%s", ilc->s);
            break;
         }
      ilc = ilc->next;
      }
   fprintf(db, " $e ");
   }
