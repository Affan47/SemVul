v_specify_block(void)
#else
v_specify_block()
#endif
{
#line 1890 "./verilog.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1890 "./verilog.g"
  zzmatch(V_SPECIFY); zzCONSUME;
#line 1890 "./verilog.g"
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (setwd28[LA(1)]&0x40) ) {
#line 1890 "./verilog.g"
      zzsetmatch(zzerr96, zzerr97); zzCONSUME;
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
#line 1890 "./verilog.g"
  zzmatch(V_ENDSPECIFY); zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd28, 0x80);
  }
}
