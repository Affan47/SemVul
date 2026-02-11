doProcess( )
{
	CObservationRangePtr obs= CObservationRange::Create();

	try
	{
		getObservation(*obs);
		m_state = ssWorking;

		if(obs->sensedData.size() > 0)
		{
			appendObservation( obs );
		}
	}
	catch(...)
	{
		m_state = ssError;
	    THROW_EXCEPTION("No observation received from the Phidget board!");
	}
}
