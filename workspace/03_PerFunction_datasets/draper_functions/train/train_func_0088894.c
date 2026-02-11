to_dec(int32 *blen)
{

 if (strchr(__numtoken, 'z') != NULL)
  { one_allbits_(__bcwrk, __itoklen); *blen = __itoklen; return; }
 else if (strchr(__numtoken, 'x') != NULL)
  {

   one_allbits_(__acwrk, __itoklen);
   one_allbits_(__bcwrk, __itoklen);
   *blen = __itoklen;
   return;
  }

 wide_strtoverdec(*blen);

 *blen = __trim1_0val(__acwrk, *blen);
}
