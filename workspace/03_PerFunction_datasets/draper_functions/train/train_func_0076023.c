execute_dwarf2_frame (void)
{

  if (cie_cfi_vec == NULL)
    create_cie_data ();

  dwarf2out_alloc_current_fde ();

  create_pseudo_cfg ();


  create_cfi_notes ();
  connect_traces ();
  add_cfis_to_fde ();


  {
    size_t i;
    dw_trace_info *ti;

    FOR_EACH_VEC_ELT (trace_info, i, ti)
      ti->regs_saved_in_regs.release ();
  }
  trace_info.release ();

  htab_delete (trace_index);
  trace_index = NULL;

  return 0;
}
