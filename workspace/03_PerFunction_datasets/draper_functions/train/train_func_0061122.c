SensorThread(TThreadParams params)
{
	using namespace mrpt::hwdrivers;
	using namespace mrpt::system;
	try
	{
		string driver_name = params.cfgFile->read_string(params.section_name,"driver","",true);
		CGenericSensorPtr	sensor = CGenericSensor::createSensorPtr(driver_name);
		if (!sensor)
			throw std::runtime_error( string("***ERROR***: Class name not recognized: ") + driver_name );


		sensor->loadConfig( *params.cfgFile, params.section_name );
		cout << format("[thread_%s] Starting...",params.section_name.c_str()) << " at " << sensor->getProcessRate() <<  " Hz" << endl;

		ASSERTMSG_(sensor->getProcessRate()>0,"process_rate must be set to a valid value (>0 Hz).");
		const int process_period_ms = mrpt::utils::round( 1000.0 / sensor->getProcessRate() );

		sensor->initialize();
		while (! allThreadsMustExit )
		{
			const TTimeStamp t0= now();
			sensor->doProcess();

			CGenericSensor::TListObservations	lstObjs;
			sensor->getObservations( lstObjs );
			{
				synch::CCriticalSectionLocker	lock (&cs_global_list_obs);
				global_list_obs.insert( lstObjs.begin(), lstObjs.end() );
			}
			lstObjs.clear();

			TTimeStamp t1= now();
			double	At = timeDifference(t0,t1);
			int At_rem_ms = process_period_ms - At*1000;
			if (At_rem_ms>0)
				mrpt::system::sleep(At_rem_ms);
		}
		sensor.clear();
		cout << format("[thread_%s] Closing...",params.section_name.c_str()) << endl;
	}
	catch (std::exception &e) {
		cerr << "[SensorThread]  Closing due to exception:\n" << e.what() << endl;
		allThreadsMustExit = true;
	}
	catch (...) {
		cerr << "[SensorThread] Untyped exception! Closing." << endl;
		allThreadsMustExit = true;
	}
}
