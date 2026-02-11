reg_expr(void)
#else
reg_expr()
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  and_expr();
  zzaRet.l=zzaArg(zztasp1,1 ).l; zzaRet.r=zzaArg(zztasp1,1 ).r;
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==OR) ) {
      zzmatch(OR); zzCONSUME;
      and_expr();
      {nfa_node *t1, *t2;
        t1 = new_nfa_node(); t2 = new_nfa_node();
        (t1)->trans[0]=zzaRet.l;
        (t1)->trans[1]=zzaArg(zztasp2,2 ).l;
        		   if (zzaRet.r != NULL) (zzaRet.r)->trans[1]=t2;
        if (zzaArg(zztasp2,2 ).r) {
          (zzaArg(zztasp2,2 ).r)->trans[1]=t2;
        }
        zzaRet.l=t1; zzaRet.r=t2;
      }
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x4);
  }
}
