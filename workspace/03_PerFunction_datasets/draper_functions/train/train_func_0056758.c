selected_chain_operator_as_target(void)
{
  assert(selected_chainop_number_rep > 0);
  assert(selected_chainop_number_rep <= static_cast<int>(chainops_rep.size()));

  selected_dynobj_repp = chainops_rep[selected_chainop_number_rep - 1].cop;


  DBC_ENSURE(selected_dynobj_repp == chainops_rep[selected_chainop_number_rep - 1].cop);

}
