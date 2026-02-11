remove_audio_output(void)
{

  DBC_REQUIRE(is_selected() == true);
  DBC_REQUIRE(connected_chainsetup() != selected_chainsetup());
  DBC_REQUIRE(get_audio_output() != 0);

  ECA_LOG_MSG(ECA_LOGGER::info, "Removing selected audio output \"" + selected_audio_output_repp->label() +
	      "\" from selected chains.");
  selected_chainsetup_repp->remove_audio_output(selected_audio_output_repp);
  selected_audio_output_repp = 0;


  DBC_ENSURE(selected_audio_output_repp == 0);

}
