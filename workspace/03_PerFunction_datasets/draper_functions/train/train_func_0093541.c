fill_related()
{


  Document::type_vec_relationships vecRelationships = get_document()->get_relationships(m_table_name);


  for(Document::type_vec_relationships::iterator iter = vecRelationships.begin(); iter != vecRelationships.end(); ++iter)
  {


  }
}
