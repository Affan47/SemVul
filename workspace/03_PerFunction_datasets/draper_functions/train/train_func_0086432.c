doProcess()
{

	if (!tryToOpenTheCOM())
	{
		m_state = ssError;
		THROW_EXCEPTION("Cannot open the serial port");
	}

	bool have_reading = false;
	std::string power_reading;
	bool time_out = false;

	while (!have_reading)
	{

		COM.purgeBuffers();
		COM.Write("R",1);


		power_reading = COM.ReadString(500,&time_out);
		if (time_out)
		{

			mrpt::system::sleep(10);
		}
		else
			have_reading = true;
	}


	const float readnum = atof(power_reading.c_str());
	const float val_ppm = readnum/1000;


	mrpt::obs::CObservationGasSensors::TObservationENose obs;
	obs.readingsVoltage.push_back(val_ppm);
	obs.sensorTypes.push_back(0x0001);

	mrpt::obs::CObservationGasSensors obsG;
	obsG.sensorLabel = this->getSensorLabel();
	obsG.m_readings.push_back(obs);
	obsG.timestamp = mrpt::system::now();

	appendObservation(mrpt::obs::CObservationGasSensorsPtr(new mrpt::obs::CObservationGasSensors(obsG)));

}
