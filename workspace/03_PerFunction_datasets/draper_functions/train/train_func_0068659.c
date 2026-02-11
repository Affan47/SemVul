insertObservation(
	const CObservation *obs,
	const CPose3D *robotPose)
{
	if (!genericMapParams.enableObservationInsertion)
		return false;

	bool done = internal_insertObservation(obs,robotPose);
	if (done)
	{
		OnPostSuccesfulInsertObs(obs);
		publishEvent( mrptEventMetricMapInsert(this,obs,robotPose) );
	}
	return done;
}
