v_identifier_nodot(void)
#else
v_identifier_nodot()
#endif
{
#line 2104 "./verilog.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  if ( (LA(1)==V_IDENTIFIER) ) {
#line 2105 "./verilog.g"
    zzmatch(V_IDENTIFIER);
#line 2105 "./verilog.g"
    zzaRet.symbol = zzaArg(zztasp1,1 ).symbol;
 zzCONSUME;

  }
  else {
    if ( (LA(1)==V_IDENTIFIER2) ) {
#line 2106 "./verilog.g"
      zzmatch(V_IDENTIFIER2);
#line 2106 "./verilog.g"
      zzaRet.symbol = zzaArg(zztasp1,1 ).symbol;
 zzCONSUME;

    }
    else {
      if ( (LA(1)==V_FUNCTION_NAME) ) {
#line 2107 "./verilog.g"
        zzmatch(V_FUNCTION_NAME);
#line 2107 "./verilog.g"
        zzaRet.symbol = zzaArg(zztasp1,1 ).symbol;
 zzCONSUME;

      }
      else {zzFAIL(1,zzerr117,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd33, 0x40);
  }
}
