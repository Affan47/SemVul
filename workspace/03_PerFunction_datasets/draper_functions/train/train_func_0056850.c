ipa_passes (void)
{
  set_cfun (NULL);
  current_function_decl = NULL;
  gimple_register_cfg_hooks ();
  bitmap_obstack_initialize (NULL);

  invoke_plugin_callbacks (PLUGIN_ALL_IPA_PASSES_START, NULL);

  if (!in_lto_p)
    {
      execute_ipa_pass_list (all_small_ipa_passes);
      if (seen_error ())
	return;
    }


  if (cgraph_state < CGRAPH_STATE_IPA_SSA)
    cgraph_state = CGRAPH_STATE_IPA_SSA;

  if (!in_lto_p)
    {

      coverage_finish ();


      set_cfun (NULL);
      current_function_decl = NULL;
      cgraph_process_new_functions ();

      execute_ipa_summary_passes
	((struct ipa_opt_pass_d *) all_regular_ipa_passes);
    }


  if (flag_generate_lto)
    targetm.asm_out.lto_start ();

  execute_ipa_summary_passes ((struct ipa_opt_pass_d *) all_lto_gen_passes);

  if (!in_lto_p)
    ipa_write_summaries ();

  if (flag_generate_lto)
    targetm.asm_out.lto_end ();

  if (!flag_ltrans)
    execute_ipa_pass_list (all_regular_ipa_passes);
  invoke_plugin_callbacks (PLUGIN_ALL_IPA_PASSES_END, NULL);

  bitmap_obstack_release (NULL);
}
