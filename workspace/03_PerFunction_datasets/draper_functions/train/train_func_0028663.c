doProcess()
{
	using namespace mrpt::obs;

	bool	thereIs, hwError;

	CObservation3DRangeScanPtr newObs = CObservation3DRangeScan::Create();

	getNextObservation( *newObs, thereIs, hwError );

	if (hwError)
	{
		m_state = ssError;
	    THROW_EXCEPTION("Couldn't communicate to the SwissRanger 3D camera!");
	}

	if (thereIs)
	{
		m_state = ssWorking;

		appendObservation( newObs );
	}
}
