register_claim_file (ld_plugin_claim_file_handler handler)
{
  ASSERT (called_plugin);
  called_plugin->claim_file_handler = handler;
  return LDPS_OK;
}
