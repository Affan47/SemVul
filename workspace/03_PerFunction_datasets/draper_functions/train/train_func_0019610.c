parse_option (const char *opt)
{
  if (!strncmp ("fail", opt, 4))
    return set_ret_val (opt + 4, LDPS_ERR);
  else if (!strncmp ("pass", opt, 4))
    return set_ret_val (opt + 4, LDPS_OK);
  else if (!strncmp ("register", opt, 8))
    return set_register_hook (opt + 8, TRUE);
  else if (!strncmp ("noregister", opt, 10))
    return set_register_hook (opt + 10, FALSE);
  else if (!strncmp ("claim:", opt, 6))
    return record_claim_file (opt + 6);
  else if (!strncmp ("sym:", opt, 4))
    return record_claimed_file_symbol (opt + 4);
  else if (!strncmp ("add:", opt, 4))
    return record_add_file (opt + 4, ADD_FILE);
  else if (!strncmp ("lib:", opt, 4))
    return record_add_file (opt + 4, ADD_LIB);
  else if (!strncmp ("dir:", opt, 4))
    return record_add_file (opt + 4, ADD_DIR);
  else if (!strcmp ("dumpresolutions", opt))
    dumpresolutions = TRUE;
  else
    return LDPS_ERR;
  return LDPS_OK;
}
