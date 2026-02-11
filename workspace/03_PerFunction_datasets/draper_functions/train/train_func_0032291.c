gen_producer_string (void)
{
  size_t j;
  VEC(dchar_p, heap) *switches = NULL;
  const char *language_string = lang_hooks.name;
  char *producer, *tail;
  const char *p;
  size_t len = dwarf_record_gcc_switches ? 0 : 3;
  size_t plen = strlen (language_string) + 1 + strlen (version_string);

  for (j = 1; dwarf_record_gcc_switches && j < save_decoded_options_count; j++)
    switch (save_decoded_options[j].opt_index)
      {
      case OPT_o:
      case OPT_d:
      case OPT_dumpbase:
      case OPT_dumpdir:
      case OPT_auxbase:
      case OPT_auxbase_strip:
      case OPT_quiet:
      case OPT_version:
      case OPT_v:
      case OPT_w:
      case OPT_L:
      case OPT_D:
      case OPT_I:
      case OPT_U:
      case OPT_SPECIAL_unknown:
      case OPT_SPECIAL_ignore:
      case OPT_SPECIAL_program_name:
      case OPT_SPECIAL_input_file:
      case OPT_grecord_gcc_switches:
      case OPT_gno_record_gcc_switches:
      case OPT__output_pch_:
      case OPT_fdiagnostics_show_location_:
      case OPT_fdiagnostics_show_option:
      case OPT_fverbose_asm:
      case OPT____:
      case OPT__sysroot_:
      case OPT_nostdinc:
      case OPT_nostdinc__:

	continue;
      default:
        gcc_checking_assert (save_decoded_options[j].canonical_option[0][0]
			     == '-');
        switch (save_decoded_options[j].canonical_option[0][1])
	  {
	  case 'M':
	  case 'i':
	  case 'W':
	    continue;
	  case 'f':
	    if (strncmp (save_decoded_options[j].canonical_option[0] + 2,
			 "dump", 4) == 0)
	      continue;
	    break;
	  default:
	    break;
	  }
	VEC_safe_push (dchar_p, heap, switches,
		       save_decoded_options[j].orig_option_with_args_text);
	len += strlen (save_decoded_options[j].orig_option_with_args_text) + 1;
	break;
      }

  producer = XNEWVEC (char, plen + 1 + len + 1);
  tail = producer;
  sprintf (tail, "%s %s", language_string, version_string);
  tail += plen;

  if (!dwarf_record_gcc_switches)
    {
#ifdef MIPS_DEBUGGING_INFO


      if (debug_info_level > DINFO_LEVEL_TERSE)
	{
	  memcpy (tail, " -g", 3);
	  tail += 3;
	}
#endif
    }

  FOR_EACH_VEC_ELT (dchar_p, switches, j, p)
    {
      len = strlen (p);
      *tail = ' ';
      memcpy (tail + 1, p, len);
      tail += len + 1;
    }

  *tail = '\0';
  VEC_free (dchar_p, heap, switches);
  return producer;
}
