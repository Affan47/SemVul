setup_incoming_promotions (rtx first)
{
  tree arg;
  bool strictly_local = false;

  for (arg = DECL_ARGUMENTS (current_function_decl); arg;
       arg = DECL_CHAIN (arg))
    {
      rtx x, reg = DECL_INCOMING_RTL (arg);
      int uns1, uns3;
      enum machine_mode mode1, mode2, mode3, mode4;


      if (!REG_P (reg))
	continue;


      strictly_local = cgraph_local_info (current_function_decl)->local;


      mode1 = TYPE_MODE (TREE_TYPE (arg));
      uns1 = TYPE_UNSIGNED (TREE_TYPE (arg));


      mode2 = TYPE_MODE (DECL_ARG_TYPE (arg));
      uns3 = TYPE_UNSIGNED (DECL_ARG_TYPE (arg));


      mode3 = promote_function_mode (DECL_ARG_TYPE (arg), mode2, &uns3,
				     TREE_TYPE (cfun->decl), 0);


      mode4 = GET_MODE (reg);


      if (mode1 == mode3)
	continue;


      if (mode3 != mode4)
	continue;

      if (mode1 == mode2)
	;


      else if (!strictly_local)
	continue;


      else if (uns1)
	uns3 = true;
      else if (uns3)
	continue;


      x = gen_rtx_CLOBBER (mode1, const0_rtx);
      x = gen_rtx_fmt_e ((uns3 ? ZERO_EXTEND : SIGN_EXTEND), mode3, x);
      record_value_for_reg (reg, first, x);
    }
}
