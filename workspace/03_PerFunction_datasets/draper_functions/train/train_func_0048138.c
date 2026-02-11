on_button_add_related()
{


    Gtk::TreeModel::iterator iter = append_appropriate_row();
    if(iter)
    {
      Gtk::TreeModel::Row row = *iter;

      sharedptr<LayoutItem_Portal> portal = sharedptr<LayoutItem_Portal>::create();

      row[m_model_items->m_columns.m_col_layout_item] = portal;


      Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_treeview_fields->get_selection();
      if(refTreeSelection)
        refTreeSelection->select(iter);

      m_treeview_fields->scroll_to_row( Gtk::TreeModel::Path(iter) );

      m_modified = true;
    }


  enable_buttons();
}
