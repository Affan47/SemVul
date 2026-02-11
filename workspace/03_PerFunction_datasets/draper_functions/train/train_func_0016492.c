__colto_eol(void)
{
 for (__last_xtk = -1;;)
  {
   if (__toktyp == TEOF) return(TRUE);
   if (__toktyp == SEMI)
    {
     __ia_err(1487, "semicolon illegal end of interactive expression");
     goto bad_end;
    }
   if (!__bld_expnode()) goto bad_end;
   __get_vtok();
  }

bad_end:
 __set_xtab_errval();
 return(FALSE);
}
