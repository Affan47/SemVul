prep_vflist(void)
{
 register int32 fi;


 if (__last_inf == __last_optf)
  __pv_terr(301, "no Verilog input files specified");
 __last_lbf = __last_inf;


 for (fi = 0; fi < MAXFILNEST; fi++) __vinstk[fi] = NULL;
 __vin_top = -1;
 __lasttoktyp = UNDEF;
 __last_attr_prefix = FALSE;

 __push_vinfil();


 __cur_infi = __last_optf + 1;
 if (!__open_sfil())
  __pv_terr(301, "no Verilog input - all files empty or cannot be opened");
}
