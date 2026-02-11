on_adddel_Delete(const Gtk::TreeModel::iterator& rowStart, const Gtk::TreeModel::iterator& rowEnd)
{
  Gtk::TreeModel::iterator iterAfter = rowEnd;
  ++iterAfter;

  bool something_changed = false;
  for(Gtk::TreeModel::iterator iter = rowStart; iter != iterAfter; ++iter)
  {
    const Glib::ustring table_name = m_AddDel.get_value_key(iter);

    if(!table_name.empty())
    {
      Document* document = get_document();
      if(document)
      {

        if(!document->get_table_is_known(table_name))
        {

           Gtk::MessageDialog dialog(_("You cannot delete this table, because there is no information about this table in the document."));
           dialog.set_transient_for(*AppWindow::get_appwindow());
           dialog.run();
        }
        else
        {

          const Glib::ustring strMsg = Glib::ustring::compose(_("Are you sure that you want to delete this table?\nTable name: %1"), table_name);
          Gtk::MessageDialog dialog(Utils::bold_message(_("Delete Table")), true);
          dialog.set_secondary_text(strMsg);
          dialog.set_transient_for(*AppWindow::get_appwindow());
          const int iButtonClicked = dialog.run();


          const Glom::Document::type_vec_fields fields = document->get_table_fields(table_name);


          if(iButtonClicked == Gtk::RESPONSE_OK)
          {
            const bool test = DbUtils::drop_table(table_name);
            if(!test)
              std::cerr << G_STRFUNC << ": DROP TABLE failed." << std::endl;
            else
            {

              get_document()->remove_table(table_name);

              something_changed = true;
            }


            for(Glom::Document::type_vec_fields::const_iterator iter = fields.begin(); iter != fields.end(); ++iter)
            {
              const Glom::sharedptr<const Glom::Field> field = *iter;
              if(!field || !field->get_auto_increment())
                continue;

              const Glib::ustring field_name = field->get_name();

              if(!field_name.empty())
                DbUtils::remove_auto_increment(table_name, field_name);
              else
              {
                std::cerr << G_STRFUNC << ": field_name is empty" << std::endl;
              }
            }
          }
        }
      }
    }
  }

  if(something_changed)
  {
    save_to_document();

    fill_from_database();
  }
}
