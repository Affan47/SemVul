loadConfig_sensorSpecific(	const mrpt::utils::CConfigFileBase &configSource,
								const std::string	  &iniSection )
{
	MRPT_START

	std::vector<double> aux;


	m_usbSerialNumber	= configSource.read_string(iniSection,"USB_serialNumber",m_usbSerialNumber,true);
	m_gain				= configSource.read_int(iniSection,"gain",m_gain,true);
	m_maxRange			= configSource.read_float(iniSection,"maxRange",m_maxRange,true);
	m_minTimeBetweenPings = configSource.read_float(iniSection,"minTimeBetweenPings",m_minTimeBetweenPings,true);

	ASSERT_( m_maxRange>0 && m_maxRange<=11 );
	ASSERT_( m_gain<=16 );


	configSource.read_vector( iniSection, "firingOrder", m_firingOrder, m_firingOrder, true );


	configSource.read_vector( iniSection, "sonarGains", aux, aux, true );

	std::vector<int32_t>::iterator itSonar;
	std::vector<double>::iterator	itAux;
	for( itSonar = m_firingOrder.begin(), itAux = aux.begin(); itSonar != m_firingOrder.end(); ++itSonar, ++itAux )
		m_sonarGains[ *itSonar ] = *itAux;

	ASSERT_( aux.size() == m_firingOrder.size() );


	aux.clear();
	for( itSonar = m_firingOrder.begin(); itSonar != m_firingOrder.end(); ++itSonar )
	{
		configSource.read_vector( iniSection, format("pose%i",*itSonar), aux, aux, true );
		m_sonarPoses[ *itSonar ] = mrpt::math::TPose3D( aux[0], aux[1], aux[2], DEG2RAD( (float)aux[3]), DEG2RAD( (float)aux[4]), DEG2RAD( (float)aux[5]) );
	}

	ASSERT_( m_sonarGains.size() == m_firingOrder.size() );

	MRPT_END
}
