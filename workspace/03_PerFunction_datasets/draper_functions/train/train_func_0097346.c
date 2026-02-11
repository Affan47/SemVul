operator==(const PseudoJet & a, const PseudoJet & b) {
  if (a.px() != b.px()) return false;
  if (a.py() != b.py()) return false;
  if (a.pz() != b.pz()) return false;
  if (a.E () != b.E ()) return false;

  if (a.user_index()    != b.user_index()) return false;
  if (a.cluster_hist_index() != b.cluster_hist_index()) return false;
  if (a.user_info_ptr() != b.user_info_ptr()) return false;
  if (a.structure_ptr() != b.structure_ptr()) return false;

  return true;
}
