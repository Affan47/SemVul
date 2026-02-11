lshift_cheap_p (void)
{
  static bool init[2] = {false, false};
  static bool cheap[2] = {true, true};

  bool speed_p = optimize_insn_for_speed_p ();

  if (!init[speed_p])
    {
      rtx reg = gen_rtx_REG (word_mode, 10000);
      int cost = set_src_cost (gen_rtx_ASHIFT (word_mode, const1_rtx, reg),
			       speed_p);
      cheap[speed_p] = cost < COSTS_N_INSNS (3);
      init[speed_p] = true;
    }

  return cheap[speed_p];
}
