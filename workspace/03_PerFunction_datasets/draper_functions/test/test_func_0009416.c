on_button_group_delete()
{
  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_treeview_groups->get_selection();
  if(refTreeSelection)
  {
    Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
    if(iter)
    {
      Gtk::TreeModel::Row row = *iter;

      const Glib::ustring group = row[m_model_columns_groups.m_col_name];
      if(!group.empty())
      {

        Gtk::MessageDialog dialog(Utils::bold_message(_("Delete Group")), true, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_OK_CANCEL);
        dialog.set_secondary_text(_("Are your sure that you wish to delete this group?"));
        dialog.set_transient_for(*this);

        int response = dialog.run();
        dialog.hide();

        if(response == Gtk::RESPONSE_OK)
        {
          const Glib::ustring strQuery = "DROP GROUP " + DbUtils::escape_sql_id(group);
          const bool test = DbUtils::query_execute_string(strQuery);
          if(!test)
            std::cerr << G_STRFUNC << ": DROP GROUP failed." << std::endl;

          fill_group_list();
        }
      }


    }
  }
}
