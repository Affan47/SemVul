m_check_expression(pIIR_ArrayRange ar, RegionStack &rstack)
{
  int error_count = 0;
  list<pIIR_DeclarativeRegion> rlist;

  if (ar->array != NULL) {
    error_count += check_expression(ar->array, rstack);
    rlist.push_back(static_declarative_region(ar->array));
  }

  if (ar->index != NULL) {
    error_count += check_expression(ar->index, rstack);
    rlist.push_back(static_declarative_region(ar->index));


    if ((ar->is(IR_ATTR_ARRAY_RANGE) ||
	 ar->is(IR_ATTR_ARRAY_REVERSE_RANGE)) &&
	ar->index->static_level != IR_LOCALLY_STATIC) {
	codegen_error.error("%:error: index parameter of attributes RANGE/REVERSE_RANGE must be locally static",
			    ar);
	error_count++;
    }
  }

  static_declarative_region(ar) = get_combined_static_region(rlist, rstack);

  return error_count;
}
