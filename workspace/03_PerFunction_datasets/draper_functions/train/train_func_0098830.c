select_chain_operator(int chainop_id)
{

  DBC_REQUIRE(is_selected() == true);
  DBC_REQUIRE(selected_chains().size() == 1);
  DBC_REQUIRE(chainop_id > 0);


  unsigned int p = selected_chainsetup_repp->first_selected_chain();
  if (p < selected_chainsetup_repp->chains.size()) {
    CHAIN *ch = selected_chainsetup_repp->chains[p];
    if (chainop_id < ch->number_of_chain_operators() + 1) {
      ch->select_chain_operator(chainop_id);
    }
  }
}
