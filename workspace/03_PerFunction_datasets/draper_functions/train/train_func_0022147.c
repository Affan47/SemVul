set_field(const sharedptr<const Field>& field, const Glib::ustring& table_name)
{
  set_blocked();

  m_Field = glom_sharedptr_clone(field);
  m_table_name = table_name;


  m_pEntry_Name->set_text(field->get_name());
  m_pCombo_Type->set_field_type( field->get_glom_type() );

  m_pCheck_Unique->set_active(field->get_unique_key());
  m_pCheck_PrimaryKey->set_active(field->get_primary_key());
  m_pCheck_AutoIncrement->set_active(field->get_auto_increment());


  bool disable_default_value = false;
  if(field->get_auto_increment())
    disable_default_value = true;


  Gnome::Gda::Value default_value;
  if(!disable_default_value)
    default_value = m_Field->get_default_value();


  delete m_pDataWidget_DefaultValueSimple;
  m_pDataWidget_DefaultValueSimple = 0;


  sharedptr<LayoutItem_Field> layout_item = sharedptr<LayoutItem_Field>::create();
  sharedptr<Field> field_default_value = glom_sharedptr_clone(m_Field);
  field_default_value->set_name("glom_temp_default_value");
  field_default_value->set_title_original(_("Default Value"));
  layout_item->set_full_field_details(field_default_value);
  m_pDataWidget_DefaultValueSimple = Gtk::manage( new DataWidget(layout_item, "", get_document()) );
  if(!m_pDataWidget_DefaultValueSimple->get_data_child_widget())
    std::cerr << G_STRFUNC << ": The DataWidget did not create a child widget." << std::endl;

  on_foreach_connect(*m_pDataWidget_DefaultValueSimple);

  Gtk::Label* pLabel = m_pDataWidget_DefaultValueSimple->get_label();
  if(!pLabel->get_text().empty())
    m_pBox_DefaultValueSimple->pack_start(*pLabel);

  m_pBox_DefaultValueSimple->pack_end(*m_pDataWidget_DefaultValueSimple, Gtk::PACK_EXPAND_WIDGET);
  m_pDataWidget_DefaultValueSimple->set_value(default_value);
  m_pDataWidget_DefaultValueSimple->show();


  m_pCheck_Lookup->set_active(m_Field->get_is_lookup());
  on_check_lookup_toggled();


  Document* document = dynamic_cast<Document*>(get_document());
  if(document)
  {
    const Document::type_vec_relationships vecRelationships = document->get_relationships(table_name);
    m_pCombo_LookupRelationship->set_relationships(vecRelationships);
  }

  sharedptr<Relationship> lookup_relationship;
  if(!disable_default_value)
    lookup_relationship = m_Field->get_lookup_relationship();

  m_pCombo_LookupRelationship->set_selected_relationship(lookup_relationship);
  on_combo_lookup_relationship_changed();

  Glib::ustring lookup_field_name;
  if(!disable_default_value)
    lookup_field_name = m_Field->get_lookup_field();
  m_pCombo_LookupField->set_active_text(lookup_field_name);


  const Glib::ustring calculation = field->get_calculation();
  if(calculation.empty())
   m_pRadio_UserEntry->set_active();
  else
    m_pRadio_Calculate->set_active();

  on_check_lookup_toggled();


  m_pTextView_Calculation->get_buffer()->set_text(calculation);


  m_pEntry_Title->set_text(item_get_title(field));


  m_box_formatting->set_formatting_for_field(field->m_default_formatting, m_table_name, field);

  set_blocked(false);

  enforce_constraints();
  Dialog_Properties::set_modified(false);
}
