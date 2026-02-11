v_parameter_override(void)
#else
v_parameter_override()
#endif
{
#line 1565 "./verilog.g"
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
#line 1565 "./verilog.g"
  zzmatch(V_DEFPARAM); zzCONSUME;
#line 1565 "./verilog.g"
  v_list_of_param_assignments();
#line 1565 "./verilog.g"
  zzmatch(V_SEMI); zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd14, 0x80);
  }
}
