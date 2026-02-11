__vskipto4_any(int32 targ1, int32 targ2, int32 targ3, int32 targ4)
{
 if (__iact_state) longjmp(__iact_jmpbuf, 1);
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2 || __toktyp == targ3
    || __toktyp == targ4)
    { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_syncto_tokclass((byte) __toktyp)) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to statement token %s",
     prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}
