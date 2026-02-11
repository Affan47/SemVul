result(const PseudoJet &jet) const {


  vector<PseudoJet> subjets;
  JetDefinition subjet_def;
  bool discard_area;


  _set_filtered_elements(jet, subjets, subjet_def, discard_area);


  vector<PseudoJet> kept, rejected;


  Selector selector_copy = _selector;
  if (selector_copy.takes_reference()) selector_copy.set_reference(jet);
  selector_copy.sift(subjets, kept, rejected);


  return _finalise(jet, kept, rejected, subjet_def, discard_area);
}
