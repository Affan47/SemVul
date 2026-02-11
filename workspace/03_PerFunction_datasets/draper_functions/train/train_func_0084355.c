v_edge(void)
#else
v_edge()
#endif
{
#line 1396 "./verilog.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  if ( (LA(1)==V_LP) ) {
#line 1396 "./verilog.g"
    zzmatch(V_LP); zzCONSUME;
#line 1396 "./verilog.g"
    v_fake_edge();
#line 1396 "./verilog.g"
    zzmatch(V_RP); zzCONSUME;
  }
  else {
    if ( (LA(1)==V_EDGE_SYMBOL)
 ) {
#line 1397 "./verilog.g"
      zzmatch(V_EDGE_SYMBOL); zzCONSUME;
    }
    else {zzFAIL(1,zzerr27,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd7, 0x2);
  }
}
