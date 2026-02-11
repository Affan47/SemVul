rest_of_handle_loop_optimize (tree decl, rtx insns)
{
  int do_unroll, do_prefetch;

  timevar_push (TV_LOOP);
  delete_dead_jumptables ();
  cleanup_cfg (CLEANUP_EXPENSIVE | CLEANUP_PRE_LOOP);
  open_dump_file (DFI_loop, decl);


  free_bb_for_insn ();

  if (flag_unroll_loops)
    do_unroll = LOOP_AUTO_UNROLL;
  else
    do_unroll = flag_old_unroll_loops ? LOOP_UNROLL : LOOP_AUTO_UNROLL;
  do_prefetch = flag_prefetch_loop_arrays ? LOOP_PREFETCH : 0;

  if (flag_rerun_loop_opt)
    {
      cleanup_barriers ();


      loop_optimize (insns, rtl_dump_file, do_unroll);
      do_unroll = 0;


      delete_trivially_dead_insns (insns, max_reg_num ());


      reg_scan (insns, max_reg_num (), 1);
    }
  cleanup_barriers ();
  loop_optimize (insns, rtl_dump_file, do_unroll | LOOP_BCT | do_prefetch);


  delete_trivially_dead_insns (insns, max_reg_num ());
  close_dump_file (DFI_loop, print_rtl, insns);
  timevar_pop (TV_LOOP);
  find_basic_blocks (insns, max_reg_num (), rtl_dump_file);

  ggc_collect ();
}
