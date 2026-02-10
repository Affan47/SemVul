add_chains(const std::vector<string>& new_chains)
{

  DBC_REQUIRE(is_selected() == true);
  DBC_REQUIRE(connected_chainsetup() != selected_chainsetup());


  selected_chainsetup_repp->add_new_chains(new_chains);
  selected_chainsetup_repp->select_chains(new_chains);

  ECA_LOG_MSG(ECA_LOGGER::info, "Added chains: " + kvu_vector_to_string(new_chains, ", ") + ".");


  DBC_ENSURE(selected_chains().size() == new_chains.size());

}
