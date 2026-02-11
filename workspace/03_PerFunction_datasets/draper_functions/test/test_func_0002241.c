NSUniqueAttr_Init(Slapi_PBlock *pb)
{
  int err = 0;
  Slapi_Entry *plugin_entry = NULL;
  char *plugin_type = NULL;
  int preadd = SLAPI_PLUGIN_PRE_ADD_FN;
  int premod = SLAPI_PLUGIN_PRE_MODIFY_FN;
  int premdn = SLAPI_PLUGIN_PRE_MODRDN_FN;

  BEGIN
    int argc;
    char **argv;


    err = slapi_pblock_set(pb, SLAPI_PLUGIN_VERSION,
            SLAPI_PLUGIN_VERSION_01);
    if (err) break;


    slapi_pblock_get (pb, SLAPI_PLUGIN_IDENTITY, &plugin_identity);


    if ((slapi_pblock_get(pb, SLAPI_PLUGIN_CONFIG_ENTRY, &plugin_entry) == 0) &&
        plugin_entry &&
        (plugin_type = slapi_entry_attr_get_charptr(plugin_entry, "nsslapd-plugintype")) &&
        plugin_type && strstr(plugin_type, "betxn")) {
        preadd = SLAPI_PLUGIN_BE_TXN_PRE_ADD_FN;
        premod = SLAPI_PLUGIN_BE_TXN_PRE_MODIFY_FN;
        premdn = SLAPI_PLUGIN_BE_TXN_PRE_MODRDN_FN;
    }
    slapi_ch_free_string(&plugin_type);


    err = slapi_pblock_get(pb, SLAPI_PLUGIN_ARGC, &argc);
    if (err) break;

    err = slapi_pblock_get(pb, SLAPI_PLUGIN_ARGV, &argv);
    if (err) break;


    if (argc < 1) { err = -1; break; }
    argv++; argc--;

    for(;argc > 0;argc--, argv++) {
        char *normdn = slapi_create_dn_string_case("%s", *argv);
        slapi_ch_free_string(argv);
        *argv = normdn;
    }


    err = slapi_pblock_set(pb, SLAPI_PLUGIN_DESCRIPTION,
            (void*)&pluginDesc);
    if (err) break;


    err = slapi_pblock_set(pb, preadd, (void*)preop_add);
    if (err) break;

    err = slapi_pblock_set(pb, premod, (void*)preop_modify);
    if (err) break;

    err = slapi_pblock_set(pb, premdn, (void*)preop_modrdn);
    if (err) break;

  END

  if (err) {
    slapi_log_error(SLAPI_LOG_PLUGIN, "NSUniqueAttr_Init",
             "Error: %d\n", err);
    err = -1;
  }
  else
    slapi_log_error(SLAPI_LOG_PLUGIN, "NSUniqueAttr_Init",
             "plugin loaded\n");

  return err;
}
