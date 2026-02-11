Substring_assign_shortexon_prob (T shortexon) {

  if (shortexon->chimera_knownp == false) {

  } else if (shortexon->plusp == shortexon->chimera_sensep) {
    shortexon->chimera_prob = Maxent_hr_acceptor_prob(shortexon->chimera_modelpos,shortexon->chroffset);
  } else {
    shortexon->chimera_prob = Maxent_hr_antiacceptor_prob(shortexon->chimera_modelpos,shortexon->chroffset);
  }


  if (shortexon->chimera_knownp_2 == false) {

  } else if (shortexon->plusp == shortexon->chimera_sensep) {
    shortexon->chimera_prob_2 = Maxent_hr_donor_prob(shortexon->chimera_modelpos_2,shortexon->chroffset);
  } else {
    shortexon->chimera_prob_2 = Maxent_hr_antidonor_prob(shortexon->chimera_modelpos_2,shortexon->chroffset);
  }

  return;
}
