gnac_profiles_properties_load_profile_from_file(const gchar  *path,
                                               const gchar   *filename,
                                               GError       **error)
{
  g_return_val_if_fail(!error || !*error, NULL);

  AudioProfileGeneric *profile;
  XMLDoc *doc = gnac_profiles_default_load_generic_audio_profile(path, &profile);
  if (!doc || !(profile->format_id)) {
    *error = g_error_new(g_quark_from_static_string("gnac"), 0,
        _("File \"%s\" is not a valid profile file."), filename);
    gnac_profiles_xml_engine_free_doc_xpath(doc);
    return NULL;
  }

  FormatModule *format_module = g_hash_table_lookup(formats, profile->format_id);
  if (!format_module) {
    *error = g_error_new(g_quark_from_static_string("gnac"), 0,
        _("Format defined by id \"%s\" in file \"%s\" is not supported."),
        profile->format_id, filename);
    gnac_profiles_utils_free_audio_profile_generic(profile);
    gnac_profiles_xml_engine_free_doc_xpath(doc);
    return NULL;
  }

  profile = format_module->funcs.load_specific_properties(doc, profile);

  gnac_profiles_xml_engine_free_doc_xpath(doc);

  return profile;
}
