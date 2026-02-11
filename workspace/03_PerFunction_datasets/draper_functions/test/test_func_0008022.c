save_chainsetup(void) throw(ECA_ERROR&)
{


  DBC_REQUIRE(selected_chainsetup_repp != 0);


  selected_chainsetup_repp->save();
}
