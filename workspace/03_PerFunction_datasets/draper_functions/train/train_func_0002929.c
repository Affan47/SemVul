__mark_st_wires(void)
{

 mark_sttypewires();

 mark_stdr_wires();
 mark_stdr_inout_wired_logic();
 if (__design_no_strens) return;


 __bld_mlevel_lists();


 for (;;)
  {
   __strenprop_chg = FALSE;
   prop_stsdown();

   prop_stsup();

   if (__debug_flg) __dbg_msg("  >>> Complete one strength marking pass.\n");

   if (!__strenprop_chg) break;
  }
}
