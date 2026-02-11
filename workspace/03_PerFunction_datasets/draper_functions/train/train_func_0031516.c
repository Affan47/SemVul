xtensa_flush_pending_output (void)
{


  if (outputting_stabs_line_debug)
    return;

  if (cur_vinsn.inside_bundle)
    as_bad (_("missing closing brace"));


  if (frag_now_fix () != 0 && frag_now->tc_frag_data.is_insn)
    {
      frag_wane (frag_now);
      frag_new (0);
      xtensa_set_frag_assembly_state (frag_now);
    }
  frag_now->tc_frag_data.is_insn = FALSE;

  xtensa_clear_insn_labels ();
}
