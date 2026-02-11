rest_of_handle_cfg (tree decl, rtx insns)
{
  open_dump_file (DFI_cfg, decl);
  if (rtl_dump_file)
    dump_flow_info (rtl_dump_file);
  if (optimize)
    cleanup_cfg (CLEANUP_EXPENSIVE
		 | (flag_thread_jumps ? CLEANUP_THREADING : 0));


  if (optimize)
    {


      reg_scan (insns, max_reg_num (), 1);
      mark_constant_function ();
    }

  close_dump_file (DFI_cfg, print_rtl_with_bb, insns);
}
