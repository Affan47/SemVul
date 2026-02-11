gnac_profiles_utils_free_basic_format_info(BasicFormatInfo *bfi)
{
  if (!bfi) return;

  g_object_unref(bfi->builder);
  gnac_profiles_xml_engine_free_doc_xpath(bfi->doc);
  g_free(bfi->pipeline);
  g_free(bfi->pipeline_encoder);
  g_free(bfi->pipeline_multiplexers);
  g_free(bfi->format_id);
  g_free(bfi->format_plugin_name);
  g_free(bfi->format_name);
  g_free(bfi->file_extension);
  g_free(bfi->description);
}
