export_to_string(DataModelIOFormat format, const std::vector<int>& cols, const std::vector<int>& rows, const Glib::RefPtr<Set>& options)
{
  gchar* retvalue = gda_data_model_export_to_string(gobj(), static_cast<GdaDataModelIOFormat>(format), cols.data(), cols.size(), rows.data(), rows.size(), options->gobj());
  Glib::ustring cppretvalue(retvalue);
  g_free(retvalue);

  return cppretvalue;
}


}
