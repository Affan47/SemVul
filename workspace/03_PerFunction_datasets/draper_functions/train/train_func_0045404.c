set_columns(Gtk::TreeView *treeview)
  {
    Gtk::TreeViewColumn *column = manage(new Gtk::TreeViewColumn);
    column->set_title(_("Name"));
    column->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
    column->set_resizable(false);
    Gtk::CellRendererPixbuf *icon_renderer = manage(new Gtk::CellRendererPixbuf);
    column->pack_start(*icon_renderer, false);
    column->set_cell_data_func(*icon_renderer,
                               sigc::mem_fun(*this, &AddinsTreeModel::name_pixbuf_cell_data_func));
    Gtk::CellRenderer *renderer = manage(new Gtk::CellRendererText);
    column->pack_start(*renderer, true);
    column->set_cell_data_func(*renderer,
                               sigc::mem_fun(*this, &AddinsTreeModel::name_cell_data_func));
    treeview->append_column(*column);
    treeview->append_column(_("Version"), m_columns.version);
  }
