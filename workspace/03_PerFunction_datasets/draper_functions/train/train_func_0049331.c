GetBooleanQuery(std::vector<CL_NS(search)::BooleanClause*>& clauses, bool disableCoord){
  if ( clauses.size() == 0 )
    return NULL;

  BooleanQuery* query = _CLNEW BooleanQuery( disableCoord );

  CND_CONDITION(query != NULL, "No memory could be allocated for query");


  for( uint32_t i=0;i<clauses.size();i++ ){

    CND_CONDITION(clauses[i] != NULL, "clauses[i] is NULL");

    query->add(clauses[i]);
  }
  return query;
}
