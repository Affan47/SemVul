getFullInfo()
{

	COM.purgeBuffers();
	COM.Write("C",1);


	std::string reading;
	reading = COM.ReadString();


	std::stringstream readings_str(reading);


	std::istream_iterator<std::string> it(readings_str);
	std::istream_iterator<std::string> endit;
	std::vector<std::string> measurements_text(it, endit);


	mrpt::obs::CObservationGasSensors::TObservationENose obs;
	mrpt::obs::CObservationGasSensors obsG;

	for (size_t k=0; k < measurements_text.size(); k++)
	{
		const float readnum = atof(measurements_text[k].c_str());
		const float val_ppm = readnum/1000.f;


		obs.readingsVoltage.push_back(val_ppm);
		obsG.m_readings.push_back(obs);
	}

	obsG.sensorLabel = this->getSensorLabel();
	obsG.timestamp = mrpt::system::now();

	return obsG;

}
