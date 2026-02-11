m_vaul_compute_static_level (pIIR_ArrayAggregate e)
{


  for (pIIR_IndexedAssociationList ial = e->indexed_association_list;
       ial; ial = ial->rest)
    {
      pIIR_IndexedAssociation ia = ial->first;
      if (ia->value && ia->value->static_level < IR_GLOBALLY_STATIC)
	return IR_NOT_STATIC;
      if (ia->is(IR_RANGE_INDEXED_ASSOCIATION)
	  && (vaul_compute_static_level (pIIR_RangeIndexedAssociation(ia)->index_range)
	      < IR_GLOBALLY_STATIC))
	return IR_NOT_STATIC;
      if (ia->is(IR_SINGLE_INDEXED_ASSOCIATION)
	  && pIIR_SingleIndexedAssociation(ia)->index
	  && (pIIR_SingleIndexedAssociation(ia)->index->static_level
	      < IR_GLOBALLY_STATIC))
	return IR_NOT_STATIC;
    }
  return IR_GLOBALLY_STATIC;
}
