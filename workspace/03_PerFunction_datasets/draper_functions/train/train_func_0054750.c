connect_mdi_signals() {
#ifdef ENABLE_SPELL
  mdi.signal_document_spell_enabled.connect(sigc::mem_fun(*this, &Window::on_document_spell_enabled_cb));
#endif
  mdi.signal_document_wrap_text.connect(sigc::mem_fun(*this, &Window::signal_document_wrap_text_cb));
  mdi.signal_document_line_numbers.connect(sigc::mem_fun(*this, &Window::signal_document_line_numbers_cb));

  mdi.signal_recent_regenerate.connect(sigc::mem_fun(menubar, &MenuBar::create_recent));

#ifdef ENABLE_HIGHLIGHT
  mdi.signal_document_highlight.connect(sigc::mem_fun(menubar, &MenuBar::set_highlight));
#endif

  mdi.signal_document_encoding_changed.connect(sigc::mem_fun(*this, &Window::signal_document_encoding_changed_cb));
  mdi.signal_document_overwrite_toggled.connect(sigc::mem_fun(*this, &Window::signal_document_overwrite_toggled_cb));
  mdi.signal_document_cursor_moved.connect(sigc::mem_fun(*this, &Window::signal_document_cursor_moved_cb));
  mdi.signal_document_file_changed.connect(sigc::mem_fun(*this, &Window::signal_document_file_changed_cb));
  mdi.signal_document_readonly.connect(sigc::mem_fun(*this, &Window::signal_document_readonly_cb));
  mdi.signal_document_can_redo.connect(sigc::mem_fun(*this, &Window::signal_document_can_redo_cb));
  mdi.signal_document_can_undo.connect(sigc::mem_fun(*this, &Window::signal_document_can_undo_cb));
  mdi.signal_document_modified.connect(sigc::mem_fun(*this, &Window::signal_document_modified_cb));
  mdi.signal_document_title_changed.connect(sigc::mem_fun(*this, &Window::signal_document_title_changed_cb));
#ifdef ENABLE_SPELL
  mdi.signal_document_dictionary_changed.connect(sigc::mem_fun(*this, &Window::signal_document_dictionary_changed_cb));
#endif

  mdi.signal_doc_activated.connect(sigc::mem_fun(*this, &Window::on_doc_activated));
  mdi.signal_reset_gui.connect(sigc::mem_fun(*this, &Window::on_reset_gui));
  mdi.signal_document_added.connect(sigc::mem_fun(*this, &Window::on_document_added_cb));
  mdi.signal_document_removed.connect(sigc::mem_fun(*this, &Window::on_document_removed_cb));


  mdi.signal_closed_document_erased.connect(sigc::mem_fun(menubar, &MenuBar::signal_closed_document_erased_cb));
  mdi.signal_closed_document_added.connect(sigc::mem_fun(menubar, &MenuBar::signal_closed_document_added));
}
