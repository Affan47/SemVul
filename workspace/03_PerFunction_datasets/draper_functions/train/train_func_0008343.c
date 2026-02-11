readFromStream(mrpt::utils::CStream &in, int version)
{

	switch(version)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		{
			in	>> power;
			if (version>=1)
				in >> sensorLabel;
			else sensorLabel="";

			if (version>=2)
					in >> timestamp;
			else 	timestamp = INVALID_TIMESTAMP;

			if (version>=3)
					in >> sensorPoseOnRobot;
			else 	sensorPoseOnRobot = CPose3D();

		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)

	};

}
