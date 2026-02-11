readFromStream(mrpt::utils::CStream &in, int version)
{
	MRPT_UNUSED_PARAM(in);
	switch(version)
	{
	case 0:
	case 1:
	case 2:
		{
			in	>> voltageMainRobotBattery
				>> voltageMainRobotComputer
				>> voltageMainRobotBatteryIsValid
				>> voltageMainRobotComputerIsValid
				>> voltageOtherBatteries
				>> voltageOtherBatteriesValid;
			if (version>=1)
				in >> sensorLabel;
			else sensorLabel="";

			if (version>=2)
					in >> timestamp;
			else 	timestamp = INVALID_TIMESTAMP;
		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)

	};

}
