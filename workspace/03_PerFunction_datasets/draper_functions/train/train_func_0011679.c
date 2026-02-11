readFromStream(mrpt::utils::CStream &in, int version)
{
	switch(version)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		{
			in >> cameraPose;

			if (version>=4)
			{
				in >> cameraParams;
			}
			else
			{
				CMatrix	 intrinsicParams, distortionParams;
				in >> distortionParams >> intrinsicParams;

				if (size(distortionParams,1)==1 && size(distortionParams,2)==5)
				{
					const CMatrixDouble15 p = distortionParams.cast<double>();
					cameraParams.setDistortionParamsVector(p);
				}
				else 	cameraParams.dist.assign(0);

				cameraParams.intrinsicParams = intrinsicParams.block(0,0,3,3).cast<double>();
			}

			in >> image;

			if (version>=1)
				in >> timestamp;

			if (version>=2)
			{
				if (version<4)
					in >> cameraParams.focalLengthMeters ;
			}
			else
				cameraParams.focalLengthMeters = 0.002;

			if (version>=3)
					in >> sensorLabel;
			else	sensorLabel = "";

		} break;
	default:
		MRPT_THROW_UNKNOWN_SERIALIZATION_VERSION(version)

	};

}
