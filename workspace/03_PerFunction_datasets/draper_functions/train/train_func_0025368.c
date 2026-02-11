description () const {
  ostringstream desc;
  desc << "GridJetPlugin plugin with ymax = " << _ymax << ", dy = " << _dy << ", dphi = " << _dphi << " (requested grid spacing was " << _requested_grid_spacing << ")";
  if (_post_jet_def.jet_algorithm() != undefined_jet_algorithm) {
    desc << ", followed by " << _post_jet_def.description();
  }
  return desc.str();
}
