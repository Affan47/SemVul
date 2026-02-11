m_check_expression(pIIR_ArrayReference ar, RegionStack &rstack)
{
  int error_count = check_expression(ar->array, rstack);

  list<pIIR_DeclarativeRegion> rlist;
  rlist.push_back(static_declarative_region(ar->array));

  pIIR_Type basic_type = get_basic_type(ar->array->subtype);
  pIIR_TypeList tl = basic_type->is(IR_ARRAY_TYPE) ?
    pIIR_ArrayType(basic_type)->index_types : pIIR_ArraySubtype(basic_type)->constraint;

  for (pIIR_ExpressionList el = ar->indices; el; el = el->rest, tl = tl->rest) {
    error_count += check_expression(el->first, rstack);
    rlist.push_back(static_declarative_region(el->first));


    if (valid_folded_value(el->first))
      error_count +=
	check_scalar_against_bounds(el->first, folded_value(el->first).long_value(), tl->first,
				    rstack, runtime_checks(ar), true);

  }

  static_declarative_region(ar) = get_combined_static_region(rlist, rstack);

  return error_count;
}
