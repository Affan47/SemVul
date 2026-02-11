navigationStep()
{
	const TState prevState = m_navigationState;
	switch ( m_navigationState )
	{
	case IDLE:
	case SUSPENDED:
		try
		{

			if ( m_lastNavigationState == NAVIGATING )
			{
				printf_debug("\n[CAbstractNavigator::navigationStep()] Navigation stopped\n");
				m_robot.stop();
				m_robot.stopWatchdog();
			}
		} catch (...) { }
		break;

	case NAV_ERROR:
		try
		{

			if ( m_lastNavigationState == NAVIGATING && m_navigationState == NAV_ERROR)
				m_robot.sendNavigationEndDueToErrorEvent();


			if ( m_lastNavigationState == NAVIGATING )
			{
				printf_debug("\n[CAbstractNavigator::navigationStep()] Stoping Navigation due to a NAV_ERROR state!\n");
				m_robot.stop();
				m_robot.stopWatchdog();
			}
		} catch (...) { }
		break;


	case NAVIGATING:
		try
		{
			if ( m_lastNavigationState != NAVIGATING )
			{
				printf_debug("\n[CAbstractNavigator::navigationStep()] Starting Navigation. Watchdog initiated...\n");
				if (m_navigationParams)
					printf_debug("[CAbstractNavigator::navigationStep()] Navigation Params:\n%s\n", m_navigationParams->getAsText().c_str() );

				m_robot.startWatchdog( 1000 );
			}


			if ( m_lastNavigationState == IDLE )
				m_robot.sendNavigationStartEvent();


			performNavigationStep();

		}
		catch (std::exception &e)
		{
			cerr << "[CAbstractNavigator::navigationStep] Exception:\n" << e.what() << endl;
		}
		catch (...)
		{
			cerr << "[CAbstractNavigator::navigationStep] Unexpected exception.\n";
		}
		break;
	};
	m_lastNavigationState = prevState;
}
