documents_menu_build()
{
  Gtk::RadioButtonGroup documents_radio;

  for (unsigned i = 0; i < _documents.size(); i++)
    {
      Gtk::MenuItem *_item = radio_item(opened_menu, documents_radio, _documents[i].get_label());
      _item->signal_activate().connect(sigc::bind<int>(sigc::mem_fun(*this, &MenuBar::signal_document_activate_cb), i));

      Gtk::MenuItem& itm = *_item;

      bool r = _documents[i].get_readonly();
      bool m = _documents[i].get_modified();
      if (r)
	document_set_readonly(itm, true);
      if (m)
	document_set_modified(itm, true);
      if ((!r) && (!m))
	document_set_normal(itm);
      _item->show();
    }
}
