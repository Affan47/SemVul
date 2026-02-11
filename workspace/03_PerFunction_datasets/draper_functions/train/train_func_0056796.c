on_button_edit()
{

  Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = m_treeview_fields->get_selection();
  if(refTreeSelection)
  {
    Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
    if(iter)
    {


      Gtk::TreeModel::Row row = *iter;

      sharedptr<LayoutItem> layout_item = row[m_model_items->m_columns.m_col_layout_item];

      sharedptr<LayoutItem_Portal> layout_portal = sharedptr<LayoutItem_Portal>::cast_dynamic(layout_item);
      if(layout_portal)
      {
        sharedptr<Relationship> relationship = offer_relationship_list(layout_portal->get_relationship());
        if(relationship)
        {
          layout_portal->set_relationship(relationship);


          m_modified = true;
        }
      }
      else
      {
        sharedptr<LayoutItem_Notebook> layout_notebook = sharedptr<LayoutItem_Notebook>::cast_dynamic(layout_item);
        if(layout_notebook)
        {
          Frame_Glom::show_ok_dialog(_("Notebook Tabs"), _("Add child groups to the notebook to add tabs."), *this);


        }
        else
        {
          sharedptr<LayoutGroup> layout_group = sharedptr<LayoutGroup>::cast_dynamic(layout_item);
          if(layout_group)
          {
            Gtk::TreeModel::Path path = m_model_items->get_path(iter);
            m_treeview_fields->set_cursor(path, *m_treeview_column_title, true );
          }
          else
          {
            sharedptr<LayoutItem_Field> layout_item_field = sharedptr<LayoutItem_Field>::cast_dynamic(layout_item);
            if(layout_item_field)
            {
              sharedptr<LayoutItem_Field> chosenitem = offer_field_list_select_one_field(layout_item_field, m_table_name, this);
              if(chosenitem)
              {
                *layout_item_field = *chosenitem;

                m_modified = true;
              }
            }
            else
            {
              sharedptr<LayoutItem_Button> layout_item_button = sharedptr<LayoutItem_Button>::cast_dynamic(layout_item);
              if(layout_item_button)
              {
                sharedptr<LayoutItem_Button> chosen = offer_button_script_edit(layout_item_button);
                if(chosen)
                {
                  *layout_item_button = *chosen;


                  m_modified = true;
                }
              }
              else
              {
                sharedptr<LayoutItem_Text> layout_item_text = sharedptr<LayoutItem_Text>::cast_dynamic(layout_item);
                if(layout_item_text)
                {
                  sharedptr<LayoutItem_Text> chosen = offer_textobject(layout_item_text);
                  if(chosen)
                  {
                    *layout_item_text = *chosen;


                    m_modified = true;
                  }
                }
                else
                {
                  sharedptr<LayoutItem_Image> layout_item_image = sharedptr<LayoutItem_Image>::cast_dynamic(layout_item);
                  if(layout_item_image)
                  {
                    sharedptr<LayoutItem_Image> chosen = offer_imageobject(layout_item_image);
                    if(chosen)
                    {
                      *layout_item_image = *chosen;


                      m_modified = true;
                    }
                  }
                }
              }
            }
          }
        }
      }

      if(m_modified)
      {
        Gtk::TreeModel::Path path = m_model_items->get_path(iter);
        m_model_items->row_changed(path, iter);
      }
    }
  }
}
