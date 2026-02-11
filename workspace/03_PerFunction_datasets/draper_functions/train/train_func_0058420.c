toElem (IRState *irs)
{
  if (e2->type->toBasetype()->ty != Tvoid)
    {
      tree t1 = convert_for_condition (e1->toElem (irs), e1->type);
      tree t2 = convert_for_condition (e2->toElem (irs), e2->type);

      return d_convert (type->toCtype(), build_boolop (TRUTH_ORIF_EXPR, t1, t2));
    }
  else
    {
      return build3 (COND_EXPR, type->toCtype(),
		     build1 (TRUTH_NOT_EXPR, boolean_type_node,
			     convert_for_condition (e1->toElem (irs), e1->type)),
		     e2->toElemDtor (irs), d_void_zero_node);
    }
}
