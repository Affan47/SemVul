plugin_get_api_version (PluginObject  *obj,
                        NPVariant     *result)
{
  INT32_TO_NPVARIANT (PLUGIN_API_VERSION, *result);
  return TRUE;
}
