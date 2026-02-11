generateKinematics(const double * r) {

  if(contrib_>0) {
    z_   = r[nDim()-1];
    y_   = r[nDim()-2];
    phi_ = r[nDim()-3]*Constants::twopi;
  }

  return MEee2gZ2qq::generateKinematics(r);
}
