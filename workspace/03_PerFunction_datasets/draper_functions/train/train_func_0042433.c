get_field_chosen() const
{
  sharedptr<LayoutItem_Field> field;

  type_list_field_items list_fields = get_fields_chosen();
  if(!(list_fields.empty()))
  {
    field = *(list_fields.begin());
  }

  if(!field)
    return field;

  if(!m_start_field)
    return field;
  else
  {


    m_start_field->set_name( field->get_name() );
    m_start_field->set_full_field_details( field->get_full_field_details() );
    m_start_field->set_relationship( field->get_relationship() );
    m_start_field->set_related_relationship( field->get_related_relationship() );

    return m_start_field;
  }
}
