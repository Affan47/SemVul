check_for_update (pIIR_Expression e)
{
  if (e->is(IR_OBJECT_REFERENCE))
    {
      pIIR_ObjectDeclaration obj = vaul_get_object_declaration (e);
      IR_Mode m = vaul_get_mode (e);
      if (obj && m == IR_IN_MODE)
	error ("%:%n (of mode in) can not be updated", e, obj);
    }


  else if (e->is(IR_RECORD_AGGREGATE))
    {
      for (pIIR_ElementAssociationList eal =
	     pIIR_RecordAggregate(e)->element_association_list;
	   eal; eal = eal->rest)
	check_for_update (eal->first->value);
    }
  else if (e->is(IR_ARRAY_AGGREGATE))
    {
      for (pIIR_IndexedAssociationList ial =
	     pIIR_ArrayAggregate(e)->indexed_association_list;
	   ial; ial = ial->rest)
	check_for_update (ial->first->value);
    }


  else if (e->is(IR_OPEN_EXPRESSION))
    {
      return;
    }

  else
    error ("%:%n can not be updated", e, e);
}
