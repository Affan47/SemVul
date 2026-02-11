readFromStream(mrpt::utils::CStream &in, int version)
{
	switch(version)
	{
	case 0:
	case 1:
	case 2:
	case 3:
		{
			CMatrix covSensorPose;
			in >> aperture >> rightToLeft  >> maxRange >> sensorPose >> covSensorPose;
			uint32_t		N,i;

			in >> N;

			scan.resize(N);
			if (N)
				in.ReadBufferFixEndianness( &scan[0], N);

			if (version>=1)
			{

				validRange.resize(N);
				if (N)
					in.ReadBuffer( &validRange[0], sizeof(validRange[0])*N );
			}
			else
			{

				validRange.resize(N);
				for (i=0;i<N;i++)
					validRange[i]= scan[i] < maxRange;
			}

			if (version>=2)
			{
				in >> stdError;
			}
			else
			{
				stdError = 0.01f;
			}

			if (version>=3)
			{
				in >> timestamp;
			}


			beamAperture = DEG2RAD(0.25f);

			deltaPitch  = 0;
			sensorLabel = "";

		} break;

	case 4:
	case 5:
	case 6:
	case 7:
		{
			uint32_t		N;

			CMatrix covSensorPose;
			in >> aperture >> rightToLeft  >> maxRange >> sensorPose;

			if (version<6)
				in  >> covSensorPose;

			in >> N;
			scan.resize(N);
			validRange.resize(N);
			if (N)
			{
				in.ReadBufferFixEndianness( &scan[0], N);
				in.ReadBuffer( &validRange[0], sizeof(validRange[0])*N );
			}
			in >> stdError;
			in.ReadBufferFixEndianness( &timestamp, 1);
			in >> beamAperture;

			if (version>=5)
			{
				in >> sensorLabel;
				in >> deltaPitch;
			}
			else
			{
				sensorLabel = "";
				deltaPitch  = 0;
			}
			if (version>=7)
			{
				bool hasIntensity;
				in >> hasIntensity;
				if (hasIntensity && N)
				{
					intensity.resize(N);
					in.ReadBufferFixEndianness( &intensity[0], N);
				}
				else
				{
					intensity.clear();
				}
			}
		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)
	};

	m_cachedMap.clear();
}
