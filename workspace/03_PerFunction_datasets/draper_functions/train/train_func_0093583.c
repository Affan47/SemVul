__col_caseexpr(void)
{
 int32 parlevel, collevel, sblevel, cblevel;

 parlevel = collevel = sblevel = cblevel = 0;
 for (__last_xtk = -1;;)
  {
   switch ((byte) __toktyp) {
    case QUEST: collevel++; break;
    case COLON:

     if (collevel > 0) collevel--;
     else if (sblevel <= 0) goto good_end;
     break;
    case LSB: sblevel++; break;
    case RSB: sblevel--; break;
    case LCB: cblevel++; break;
    case RCB: cblevel--; break;
    case LPAR: parlevel++; break;
    case RPAR: parlevel--; break;
    case COMMA:
     if (parlevel <= 0 && cblevel <= 0) goto good_end;
     break;
    case TEOF:
    case SEMI:
     if (__pv_err_cnt <= __saverr_cnt)
      __pv_ferr(1101, "illegal token %s in case item expression",
       __prt_vtok());
bad_end:
     __set_xtab_errval();
     return(FALSE);
   }
   if (!__bld_expnode()) goto bad_end;
   __get_vtok();
  }
good_end:
 if (__last_xtk == -1)
  {

   __pv_ferr(1098, "case expression list missing");
   goto bad_end;
  }
 return(TRUE);
}
