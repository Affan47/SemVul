Dialog_Notebook(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
: Dialog_Layout(cobject, builder, false ),
  m_treeview(0),
  m_button_up(0),
  m_button_down(0),
  m_button_add(0),
  m_button_delete(0)
{
  builder->get_widget("treeview", m_treeview);
  if(m_treeview)
  {
    m_model = Gtk::ListStore::create(m_ColumnsTabs);
    m_treeview->set_model(m_model);


    m_treeview->append_column_editable(_("Name"), m_ColumnsTabs.m_col_name);
    m_treeview->append_column_editable(_("Title"), m_ColumnsTabs.m_col_title);


    m_model->set_sort_column(m_ColumnsTabs.m_col_sequence, Gtk::SORT_ASCENDING);


    Glib::RefPtr<Gtk::TreeView::Selection> refSelection = m_treeview->get_selection();
    if(refSelection)
    {
      refSelection->signal_changed().connect( sigc::mem_fun(*this, &Dialog_Notebook::on_treeview_selection_changed) );
    }

    m_model->signal_row_changed().connect( sigc::mem_fun(*this, &Dialog_Notebook::on_treemodel_row_changed) );
  }


  builder->get_widget("button_up", m_button_up);
  m_button_up->signal_clicked().connect( sigc::mem_fun(*this, &Dialog_Notebook::on_button_up) );

  builder->get_widget("button_down", m_button_down);
  m_button_down->signal_clicked().connect( sigc::mem_fun(*this, &Dialog_Notebook::on_button_down) );

  builder->get_widget("button_delete", m_button_delete);
  m_button_delete->signal_clicked().connect( sigc::mem_fun(*this, &Dialog_Notebook::on_button_delete) );

  builder->get_widget("button_add", m_button_add);
  m_button_add->signal_clicked().connect( sigc::mem_fun(*this, &Dialog_Notebook::on_button_add) );

  show_all_children();
}
