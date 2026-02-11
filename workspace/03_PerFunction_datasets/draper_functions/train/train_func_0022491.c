clear_chains(void)
{

  DBC_REQUIRE(is_selected() == true);
  DBC_REQUIRE(is_running() != true);

  selected_chainsetup_repp->clear_chains();
}
