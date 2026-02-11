dw2_output_call_site_table (int cs_format, int section)
{
  int n = VEC_length (call_site_record, crtl->eh.call_site_record[section]);
  int i;
  const char *begin;

  if (section == 0)
    begin = current_function_func_begin_label;
  else if (first_function_block_is_cold)
    begin = crtl->subsections.hot_section_label;
  else
    begin = crtl->subsections.cold_section_label;

  for (i = 0; i < n; ++i)
    {
      struct call_site_record_d *cs =
	VEC_index (call_site_record, crtl->eh.call_site_record[section], i);
      char reg_start_lab[32];
      char reg_end_lab[32];
      char landing_pad_lab[32];

      ASM_GENERATE_INTERNAL_LABEL (reg_start_lab, "LEHB", call_site_base + i);
      ASM_GENERATE_INTERNAL_LABEL (reg_end_lab, "LEHE", call_site_base + i);

      if (cs->landing_pad)
	ASM_GENERATE_INTERNAL_LABEL (landing_pad_lab, "L",
				     CODE_LABEL_NUMBER (cs->landing_pad));


      if (cs_format == DW_EH_PE_uleb128)
	{
	  dw2_asm_output_delta_uleb128 (reg_start_lab, begin,
					"region %d start", i);
	  dw2_asm_output_delta_uleb128 (reg_end_lab, reg_start_lab,
					"length");
	  if (cs->landing_pad)
	    dw2_asm_output_delta_uleb128 (landing_pad_lab, begin,
					  "landing pad");
	  else
	    dw2_asm_output_data_uleb128 (0, "landing pad");
	}
      else
	{
	  dw2_asm_output_delta (4, reg_start_lab, begin,
				"region %d start", i);
	  dw2_asm_output_delta (4, reg_end_lab, reg_start_lab, "length");
	  if (cs->landing_pad)
	    dw2_asm_output_delta (4, landing_pad_lab, begin,
				  "landing pad");
	  else
	    dw2_asm_output_data (4, 0, "landing pad");
	}
      dw2_asm_output_data_uleb128 (cs->action, "action");
    }

  call_site_base += n;
}
