m_check_expression(pIIR_FunctionCall fc, RegionStack &rstack)
{
  int error_count = 0;


  error_count += explore_and_check(fc->function, rstack, false);

  list<pIIR_DeclarativeRegion> rlist;
  for (pIIR_AssociationList al = fc->parameter_association_list; al; al = al->rest) {
    error_count += check_expression(al->first->actual, rstack);

    rlist.push_back(static_declarative_region(al->first->actual));
  }


  switch (get_operator_type(fc->function)) {
  case NO_OP:


    rlist.push_back(ActiveDeclarativeRegion(rstack)); break;
  default:


    rlist.push_back(RootDeclarativeRegion(rstack)); break;
  }

  static_declarative_region(fc) = get_combined_static_region(rlist, rstack);

  return error_count;
}
