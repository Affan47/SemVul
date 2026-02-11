change_chainsetup_position_samples(SAMPLE_SPECS::sample_pos_t samples)
{

  DBC_REQUIRE(is_selected());


  if (connected_chainsetup() == selected_chainsetup() && is_engine_ready_for_commands() == true) {
    change_chainsetup_position(static_cast<double>(samples) /
			       selected_chainsetup_repp->samples_per_second());
  }
  else {
    selected_chainsetup_repp->seek_position_in_samples(selected_chainsetup_repp->position_in_samples()
						       + samples );
  }
}
