rest_of_handle_sms (void)
{
#ifdef INSN_SCHEDULING
  basic_block bb;


  cfg_layout_initialize (0);
  sms_schedule ();


  max_regno = max_reg_num ();


  FOR_EACH_BB (bb)
    if (bb->next_bb != EXIT_BLOCK_PTR)
      bb->aux = bb->next_bb;
  free_dominance_info (CDI_DOMINATORS);
  cfg_layout_finalize ();
#endif
  return 0;
}
