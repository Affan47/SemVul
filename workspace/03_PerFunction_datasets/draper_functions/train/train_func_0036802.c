clear()
{


  m_sample_model.reset();
  Utils::treeview_delete_all_columns(m_sample_view);
  m_sample_view->set_model(m_sample_model);
  m_field_model.reset();
  m_field_model_sorted.reset();
  m_fields.clear();
  m_file_uri.clear();
  m_parser->clear();

  m_encoding_info->set_text("");
  m_sample_view->set_sensitive(false);
  m_encoding_combo->set_sensitive(false);
  m_first_line_as_title->set_sensitive(false);
  m_sample_rows->set_sensitive(false);

  validate_primary_key();
}
