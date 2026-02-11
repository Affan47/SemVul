m_emit_expr (pIIR_RecordAggregate ra)
{
  printf ("{ ");
  for (pIIR_ElementAssociationList al = ra->element_association_list;
       al; al = al->rest)
    {
      emit_id (al->first->element->declarator);
      printf (": ");
      emit (al->first->value);
      if (al->rest)
	printf (", ");
    }
  printf (" }");
}
