gftp_set_global_option (const char * key, const void *value)
{
  gftp_config_vars * tmpconfigvar, newconfigvar;
  void *nc_ptr;
  int ret;

  if (gftp_global_options_htable != NULL &&
      (tmpconfigvar = g_hash_table_lookup (gftp_global_options_htable,
                                           key)) != NULL)
    {
      memcpy (&newconfigvar, tmpconfigvar, sizeof (newconfigvar));


      memcpy (&nc_ptr, &value, sizeof (nc_ptr));
      newconfigvar.value = nc_ptr;
      newconfigvar.flags &= ~GFTP_CVARS_FLAGS_DYNMEM;

      ret = gftp_option_types[tmpconfigvar->otype].compare_function (&newconfigvar, tmpconfigvar);
      if (ret != 0)
        {
          gftp_option_types[tmpconfigvar->otype].copy_function (&newconfigvar, tmpconfigvar);
          gftp_configuration_changed = 1;
        }
    }
  else
    {
      fprintf (stderr, _("FATAL gFTP Error: Config option '%s' not found in global hash table\n"), key);
      exit (EXIT_FAILURE);
    }
}
