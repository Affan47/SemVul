_cmd_workaround_flags (char **argv)
{
  assert (argv);

  if (argv[1])
    {
      unsigned int outofband_flags, outofband_2_0_flags, inband_flags;

      if (parse_workaround_flags_tool (argv[1],
				       &outofband_flags,
				       &outofband_2_0_flags,
				       &inband_flags, NULL) < 0)
        ipmipower_cbuf_printf (ttyout,
                               "%s invalid workaround flags specified\n",
                               argv[1]);
      else
        {
          cmd_args.common.workaround_flags_outofband = outofband_flags;
          cmd_args.common.workaround_flags_outofband_2_0 = outofband_2_0_flags;
          cmd_args.common.workaround_flags_inband = inband_flags;
          ipmipower_cbuf_printf (ttyout,
                                 "workaround flags are now %s\n",
                                 argv[1]);
        }
    }
  else
    ipmipower_cbuf_printf (ttyout,
                           "workaround_flags must be specified: %s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
			   IPMI_PARSE_WORKAROUND_FLAGS_NONE_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_AUTHENTICATION_CAPABILITIES_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_ACCEPT_SESSION_ID_ZERO_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_FORCE_PERMSG_AUTHENTICATION_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_CHECK_UNEXPECTED_AUTHCODE_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_BIG_ENDIAN_SEQUENCE_NUMBER_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_2_0_INTEL_2_0_SESSION_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_2_0_SUPERMICRO_2_0_SESSION_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_2_0_SUN_2_0_SESSION_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_2_0_OPEN_SESSION_PRIVILEGE_STR,
                           IPMI_PARSE_WORKAROUND_FLAGS_OUTOFBAND_2_0_NON_EMPTY_INTEGRITY_CHECK_VALUE_STR);
}
