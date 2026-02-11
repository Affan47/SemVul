number_of_chain_operator_parameters(int index) const
{
  DBC_REQUIRE(index > 0);
  DBC_REQUIRE(index <= number_of_chain_operators());
  if (index > 0 &&
      index <= number_of_chain_operators())
    return chainops_rep[index - 1].cop->number_of_params();

  return -1;
}
