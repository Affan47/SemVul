transition_applies (insn_pattern *initial_insn,
		    const char *from_string ATTRIBUTE_UNUSED,
		    const char *to_string ATTRIBUTE_UNUSED)
{
  ReqOption *req_option;

  for (req_option = initial_insn->options;
       req_option != NULL;
       req_option = req_option->next)
    {
      ReqOrOption *req_or_option = req_option->or_option_terms;

      if (req_or_option == NULL
	  || req_or_option->next != NULL)
	continue;

      if (strncmp (req_or_option->option_name, "IsaUse", 6) == 0)
	{
	  bfd_boolean option_available = FALSE;
	  char *option_name = req_or_option->option_name + 6;
	  if (!strcmp (option_name, "DensityInstruction"))
	    option_available = (XCHAL_HAVE_DENSITY == 1);
	  else if (!strcmp (option_name, "L32R"))
	    option_available = (XCHAL_HAVE_L32R == 1);
	  else if (!strcmp (option_name, "Const16"))
	    option_available = (XCHAL_HAVE_CONST16 == 1);
	  else if (!strcmp (option_name, "Loops"))
	    option_available = (XCHAL_HAVE_LOOPS == 1);
	  else if (!strcmp (option_name, "WideBranches"))
	    option_available
	      = (XCHAL_HAVE_WIDE_BRANCHES == 1 && produce_flix == FLIX_ALL);
	  else if (!strcmp (option_name, "PredictedBranches"))
	    option_available
	      = (XCHAL_HAVE_PREDICTED_BRANCHES == 1
		 && produce_flix == FLIX_ALL);
	  else if (!strcmp (option_name, "Booleans"))
	    option_available = (XCHAL_HAVE_BOOLEANS == 1);
	  else
	    as_warn (_("invalid configuration option '%s' in transition rule '%s'"),
		     req_or_option->option_name, from_string);
	  if ((option_available ^ req_or_option->is_true) != 0)
	    return FALSE;
	}
      else if (strcmp (req_or_option->option_name, "realnop") == 0)
	{
	  bfd_boolean nop_available =
	    (xtensa_opcode_lookup (xtensa_default_isa, "nop")
	     != XTENSA_UNDEFINED);
	  if ((nop_available ^ req_or_option->is_true) != 0)
	    return FALSE;
	}
    }
  return TRUE;
}
