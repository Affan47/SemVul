loadConfig_sensorSpecific(
	const mrpt::utils::CConfigFileBase &configSource,
	const std::string	  &iniSection )
{
	m_serialNumber = configSource.read_string(iniSection,"SICKUSB_serialNumber",m_serialNumber);
	m_sensorPose = CPose3D(
		configSource.read_float(iniSection,"pose_x",0),
		configSource.read_float(iniSection,"pose_y",0),
		configSource.read_float(iniSection,"pose_z",0),
		DEG2RAD( configSource.read_float(iniSection,"pose_yaw",0) ),
		DEG2RAD( configSource.read_float(iniSection,"pose_pitch",0) ),
		DEG2RAD( configSource.read_float(iniSection,"pose_roll",0) )
		);

	C2DRangeFinderAbstract::loadCommonParams(configSource, iniSection);
}
