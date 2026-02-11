preDestructor()
{
	m_closing_navigator = true;


	m_critZoneNavigating.enter();
	m_critZoneNavigating.leave();


	try {
		m_robot.stop();
	} catch (...) { }

	mrpt::utils::delete_safe(m_logFile);


	this->deleteHolonomicObjects();
}
