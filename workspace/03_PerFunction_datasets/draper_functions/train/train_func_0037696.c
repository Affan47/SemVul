dwarf2out_frame_finish (void)
{

  if (targetm.debug_unwind_info () == UI_DWARF2)
    output_call_frame_info (0);


  if ((flag_unwind_tables || flag_exceptions)
      && targetm_common.except_unwind_info (&global_options) == UI_DWARF2)
    output_call_frame_info (1);
}
