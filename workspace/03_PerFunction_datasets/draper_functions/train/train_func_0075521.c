transtore_trmsg(struct net_t *np, int32 bi, int32 chg, word32 nav,
 word32 nbv)
{
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN];
 byte sb2;

 if (np->n_stren)
  {
   strcpy(s1, " strength");
   sb2 = (byte) nav;
   __st_regab_tostr(s2, &sb2, 1);
  }
 else
  {
   strcpy(s1, "");
   __regab_tostr(s2, &nav, &nbv, 1, BHEX, FALSE);
  }
 if (np->n_isavec) sprintf(s3, "%s[%d]", np->nsym->synam, bi);
 else strcpy(s3, np->nsym->synam);
 if (chg)
  __tr_msg("## tran/inout channel store of%s %s %s NV=%s\n", s1,
   __to_wtnam(s4, np), s3, s2);
 else
  __tr_msg("## tran/inout channel no change of%s %s %s OV=%s\n",
   s1, __to_wtnam(s4, np), s3, s2);
}
