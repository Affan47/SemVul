handle_common_deferred_options (void)
{
  unsigned int i;
  cl_deferred_option *opt;
  VEC(cl_deferred_option,heap) *vec
    = (VEC(cl_deferred_option,heap) *) common_deferred_options;

  if (flag_dump_all_passed)
    enable_rtl_dump_file ();

  FOR_EACH_VEC_ELT (cl_deferred_option, vec, i, opt)
    {
      switch (opt->opt_index)
	{
	case OPT_fcall_used_:
	  fix_register (opt->arg, 0, 1);
	  break;

	case OPT_fcall_saved_:
	  fix_register (opt->arg, 0, 0);
	  break;

	case OPT_fdbg_cnt_:
	  dbg_cnt_process_opt (opt->arg);
	  break;

	case OPT_fdbg_cnt_list:
	  dbg_cnt_list_all_counters ();
	  break;

	case OPT_fdebug_prefix_map_:
	  add_debug_prefix_map (opt->arg);
	  break;

	case OPT_fdump_:
	  if (!dump_switch_p (opt->arg))
	    error ("unrecognized command line option %<-fdump-%s%>", opt->arg);
	  break;

	case OPT_fenable_:
	case OPT_fdisable_:
	  if (opt->opt_index == OPT_fenable_)
	    enable_pass (opt->arg);
          else
	    disable_pass (opt->arg);
          break;

	case OPT_ffixed_:

	  fix_register (opt->arg, 1, 1);
	  break;

	case OPT_fplugin_:
#ifdef ENABLE_PLUGIN
	  add_new_plugin (opt->arg);
#else
	  error ("plugin support is disabled; configure with --enable-plugin");
#endif
	  break;

	case OPT_fplugin_arg_:
#ifdef ENABLE_PLUGIN
	  parse_plugin_arg_opt (opt->arg);
#else
	  error ("plugin support is disabled; configure with --enable-plugin");
#endif
	  break;

	case OPT_frandom_seed:

	  if (!opt->value)
	    set_random_seed (NULL);
	  break;

	case OPT_frandom_seed_:
	  set_random_seed (opt->arg);
	  break;

	case OPT_fstack_limit:

	  if (!opt->value)
	    stack_limit_rtx = NULL_RTX;
	  break;

	case OPT_fstack_limit_register_:
	  {
	    int reg = decode_reg_name (opt->arg);
	    if (reg < 0)
	      error ("unrecognized register name %qs", opt->arg);
	    else
	      stack_limit_rtx = gen_rtx_REG (Pmode, reg);
	  }
	  break;

	case OPT_fstack_limit_symbol_:
	  stack_limit_rtx = gen_rtx_SYMBOL_REF (Pmode, ggc_strdup (opt->arg));
	  break;

	default:
	  gcc_unreachable ();
	}
    }
}
