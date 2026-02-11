update_configuration (UDisksLinuxBlock  *block,
                      UDisksDaemon      *daemon)
{
  GVariant *configuration;
  GError *error;

  error = NULL;
  configuration = calculate_configuration (block, daemon, FALSE, &error);
  if (configuration == NULL)
    {
      udisks_warning ("Error loading configuration: %s (%s, %d)",
                      error->message, g_quark_to_string (error->domain), error->code);
      g_error_free (error);
      configuration = g_variant_new ("a(sa{sv})", NULL);
    }
  udisks_block_set_configuration (UDISKS_BLOCK (block), configuration);
}
