TextBuffer(Conf& conf) : _conf(conf)
#ifdef ENABLE_HIGHLIGHT
    , Gtk::TextBuffer(GTK_TEXT_BUFFER(gtk_source_buffer_new(NULL)))
#endif
{
  _insert = create_mark(begin());
  _erase = 0;
#ifdef ENABLE_HIGHLIGHT

  gtk_source_buffer_set_max_undo_levels(GTK_SOURCE_BUFFER(gobj()), 0);
#endif
#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  on_insert_conn = signal_insert().connect(sigc::mem_fun(this, &TextBuffer::on_insert), false);
  signal_erase().connect(sigc::mem_fun(this, &TextBuffer::on_erase), false);
#endif
}
