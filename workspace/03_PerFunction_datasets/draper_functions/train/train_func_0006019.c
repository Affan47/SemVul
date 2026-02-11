evaluate(const vector<double>& point) {

  assert(!wrapping());
  assert(prepared);
  assert(generator());

  DipoleSplittingInfo& split =
    ( !presampling ? generatedSplitting : presampledSplitting );

  split.continuesEvolving();

  size_t shift = 4;

  if ( presampling ) {

    split.scale(point[3] * generator()->maximumCMEnergy());

    if ( split.index().emitterPDF().pdf() &&
	 split.index().spectatorPDF().pdf() ) {
      split.emitterX(point[4]);
      split.spectatorX(point[5]);
      shift += 2;
    }

    if ( split.index().emitterPDF().pdf() &&
	 !split.index().spectatorPDF().pdf() ) {
      split.emitterX(point[4]);
      ++shift;
    }

    if ( !split.index().emitterPDF().pdf() &&
	 split.index().spectatorPDF().pdf() ) {
      split.spectatorX(point[4]);
      ++shift;
    }

    if ( splittingReweight() )
      ++shift;

    if ( splittingKernel()->nDimAdditional() )
      copy(point.begin()+shift,point.end(),split.splittingParameters().begin());

    split.hardPt(split.splittingKinematics()->ptMax(split.scale(),
						    split.emitterX(),
						    split.spectatorX(),
						    split.index(),
						    *splittingKernel()));

  }

  if ( ! split.splittingKinematics()->generateSplitting(point[0],point[1],point[2],split) ) {
    split.lastValue(0.);
    return 0.;
  }

  split.splittingKinematics()->prepareSplitting(split);

  if ( split.stoppedEvolving() ) {
    split.lastValue(0.);
    return 0.;
  }

  double kernel = splittingKernel()->evaluate(split);
  if ( splittingReweight() ) {
    if ( !presampling )
      kernel *= splittingReweight()->evaluate(split);
    else
      kernel *= point[shift-1];
  }
  double jac = split.splittingKinematics()->jacobian();

  split.lastValue( abs(jac) * kernel );

  if ( kernel < 0. )
    return 0.;

  return split.lastValue();

}
