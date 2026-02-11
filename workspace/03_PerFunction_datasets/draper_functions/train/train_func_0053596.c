on_checkbutton_related_relationships_toggled()
{
  if(!m_document)
    return;

  const bool show_related_relationships = m_checkbutton_show_related_relationships->get_active();


  sharedptr<Relationship> related_relationship;
  sharedptr<Relationship> relationship = m_combo_relationship->get_selected_relationship(related_relationship);


  m_combo_relationship->set_relationships(m_document, m_table_name, show_related_relationships);

  m_combo_relationship->set_selected_relationship(relationship, related_relationship);
}
