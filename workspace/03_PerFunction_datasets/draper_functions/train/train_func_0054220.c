set_percussion(float percussion,float perc_multiplier,float percfade) {
  my_percussion = percussion;
  my_perc_multiplier = perc_multiplier;
  my_percfade = percfade;

  for (x = 0; x < numofvoices;x++)
    voices[x]->set_percussion(percussion,perc_multiplier,percfade);

  voices[numofvoices]->set_percussion(percussion * .3f, perc_multiplier,
				      percfade);
}
