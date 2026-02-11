loadConfig_sensorSpecific(
	const mrpt::utils::CConfigFileBase &configSource,
	const string	  &iniSection )
{
	MRPT_START
	m_usbSerialNumber	= configSource.read_string( iniSection, "USB_serialname", "", true );

	m_mSensorPose.setFromValues(
        configSource.read_float( iniSection, "mPose_x", 0, false ),
        configSource.read_float( iniSection, "mPose_y", 0, false ),
        configSource.read_float( iniSection, "mPose_z", 0, false ),
        DEG2RAD( configSource.read_float( iniSection, "mPose_yaw", 0, false ) ),
        DEG2RAD( configSource.read_float( iniSection, "mPose_pitch", 0, false ) ),
        DEG2RAD( configSource.read_float( iniSection, "mPose_roll", 0, false ) ) );

	m_sSensorPose.setFromValues(
        configSource.read_float( iniSection, "sPose_x", 0, false ),
        configSource.read_float( iniSection, "sPose_y", 0, false ),
        configSource.read_float( iniSection, "sPose_z", 0, false ),
        DEG2RAD( configSource.read_float( iniSection, "sPose_yaw", 0, false ) ),
        DEG2RAD( configSource.read_float( iniSection, "sPose_pitch", 0, false ) ),
        DEG2RAD( configSource.read_float( iniSection, "sPose_roll", 0, false ) ) );

	MRPT_END
}
