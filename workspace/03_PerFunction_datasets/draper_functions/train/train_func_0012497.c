__unget_vtok(void)
{
 __lasttoktyp = __toktyp;
 strcpy(__lasttoken, __token);


 __last_attr_prefix = __attr_prefix;


 if (__toktyp == NUMBER)
  {
   int32 wlen;

   __lastitokbase = __itokbase;
   __lastitoksized = __itoksized;
   __lastitoksizdflt = __itoksizdflt;
   __lastitok_signed = __itok_signed;
   __lastitoklen = __itoklen;


   wlen = wlen_(__itoklen);
   __lastacwrk = (word32 *) __my_malloc(wlen*WRDBYTES);
   __lastbcwrk = (word32 *) __my_malloc(wlen*WRDBYTES);
   memcpy(__lastacwrk, __acwrk, wlen*WRDBYTES);
   memcpy(__lastbcwrk, __bcwrk, wlen*WRDBYTES);
   return;
  }
 if (__toktyp == REALNUM)
  {
   __lastitokbase = __itokbase;
   __lastitoksized = __itoksized;
   __lastitoksizdflt = __itoksizdflt;
   __lastitok_signed = __itok_signed;
   __lastitoklen = __itoklen;
   __lastitok_realval = __itok_realval;
  }
}
