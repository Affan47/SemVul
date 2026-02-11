controller_parameter_name(void) const
{

  DBC_REQUIRE(selected_controller() > 0);
  DBC_REQUIRE(selected_controller_parameter() > 0);

  return selected_controller_repp->get_parameter_name(selected_controller_parameter());
}
