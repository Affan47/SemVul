scaledBornScreen() const {

  if ( projectionDipole()->verbose() )
    generator()->log() << "'" << name() << "' evaluating Born screening\n";

  Energy scale = projectionDipole()->lastDipoleScale();
  Energy pt = projectionDipole()->lastPt();

  if ( projectionDipole()->verbose() )
    generator()->log() << "from pt/GeV = " << (pt/GeV)
		       << " scale/GeV = " << (scale/GeV)
		       << "\n" << flush;

  return pow(pt/scale,4.);

}
