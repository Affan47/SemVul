get_chain(void) const
{

  DBC_REQUIRE(is_selected() == true);
  DBC_REQUIRE(selected_chains().size() == 1);

  return get_chain_priv();

}
