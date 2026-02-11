loadConfig_sensorSpecific(	const mrpt::utils::CConfigFileBase *configSource,
								const std::string	  &iniSection )
{
	configSource->read_vector(iniSection.c_str(),"gain0",gain,gain);
	m_serialNumber = configSource->read_string(iniSection.c_str(),"OREJA_serialNumber",m_serialNumber);
	head_yaw = configSource->read_int(iniSection.c_str(),"HeadYaw",head_yaw);
	head_pitch = configSource->read_int(iniSection.c_str(),"HeadPitch",head_pitch);
}
