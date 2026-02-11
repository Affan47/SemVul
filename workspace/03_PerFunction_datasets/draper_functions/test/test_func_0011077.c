add_ghosts(vector<PseudoJet> & event) const {

  double rap_offset;
  int nrap_upper;
  if (_fj2_placement) {
    rap_offset  = 0.0;
    nrap_upper  = _nrap;
  } else {
    rap_offset  = 0.5;
    nrap_upper  = _nrap-1;
  }


  for (int irap = -_nrap; irap <= nrap_upper; irap++) {
    for (int iphi = 0; iphi < _nphi; iphi++) {


      double phi_fj2 = (iphi+0.5) * _dphi + _dphi*(_our_rand()-0.5)*_grid_scatter;
      double phi;
      if (_fj2_placement) phi = 0.5*pi - phi_fj2;
      else                phi = phi_fj2;
      double rap = (irap+rap_offset) * _drap + _drap*(_our_rand()-0.5)*_grid_scatter
	                                                 + _ghost_rap_offset ;
      double pt = _mean_ghost_pt*(1+(_our_rand()-0.5)*_pt_scatter);

      double exprap = exp(+rap);
      double pminus = pt/exprap;
      double pplus  = pt*exprap;
      double px = pt*cos(phi);
      double py = pt*sin(phi);
      PseudoJet mom(px,py,0.5*(pplus-pminus),0.5*(pplus+pminus));


      mom.set_cached_rap_phi(rap,phi);


      if (_selector.worker().get() && !_selector.pass(mom)) continue;
      event.push_back(mom);
    }
  }
}
