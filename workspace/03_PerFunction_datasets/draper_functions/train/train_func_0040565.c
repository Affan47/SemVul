connect_signals(Document *doc) {

  doc->signal_modified_set.connect(sigc::mem_fun(this, &MDI::signal_document_modified_cb));
  doc->signal_can_undo.connect(sigc::mem_fun(this, &MDI::signal_document_can_undo_cb));
  doc->signal_can_redo.connect(sigc::mem_fun(this, &MDI::signal_document_can_redo_cb));
  doc->signal_readonly_set.connect(sigc::mem_fun(this, &MDI::signal_document_readonly_cb));
  doc->signal_file_changed.connect(sigc::mem_fun(this, &MDI::signal_document_file_changed_cb));
  doc->signal_cursor_moved.connect(sigc::mem_fun(this, &MDI::signal_document_cursor_moved_cb));
  doc->signal_encoding_changed.connect(sigc::mem_fun(this, &MDI::signal_document_encoding_changed_cb));
  doc->signal_overwrite_toggled.connect(sigc::mem_fun(this, &MDI::signal_document_overwrite_toggled_cb));
  doc->signal_title_changed.connect(sigc::mem_fun(this, &MDI::signal_document_title_changed_cb));
#ifdef ENABLE_SPELL
  doc->signal_auto_spell_set.connect(sigc::mem_fun(this, &MDI::signal_document_spell_enabled_cb));
  doc->signal_dictionary_changed.connect(sigc::mem_fun(this, &MDI::signal_dictionary_changed_cb));
#endif
  doc->signal_wrap_text_set.connect(sigc::mem_fun(this, &MDI::signal_document_wrap_text_cb));
  doc->signal_line_numbers_set.connect(sigc::mem_fun(this, &MDI::signal_document_line_numbers_cb));
  doc->signal_dict_lookup_request.connect(sigc::mem_fun(this, &MDI::signal_document_dict_lookup_cb));
#ifdef ENABLE_HIGHLIGHT
  doc->signal_highlight_set.connect(sigc::mem_fun(this, &MDI::signal_document_highlight_cb));
#endif
  doc->signal_text_view_request_file_open.connect(sigc::mem_fun(*this, &MDI::signal_text_view_request_file_open_cb));
}
