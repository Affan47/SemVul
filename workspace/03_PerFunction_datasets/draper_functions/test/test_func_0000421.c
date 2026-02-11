_resize_and_zero_AA () {

  _average_area.resize(2*_jets.size());  _average_area  = 0.0;
  _average_area2.resize(2*_jets.size()); _average_area2 = 0.0;
  _average_area_4vector.resize(2*_jets.size());
  _average_area_4vector = PseudoJet(0.0,0.0,0.0,0.0);
  _non_jet_area = 0.0; _non_jet_area2 = 0.0; _non_jet_number=0.0;
}
