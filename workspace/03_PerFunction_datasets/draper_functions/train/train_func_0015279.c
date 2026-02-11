saveToConfigFile(const std::string &section,  mrpt::utils::CConfigFileBase &cfg ) const
{


	leftCamera.saveToConfigFile(section+string("_LEFT"), cfg);
	rightCamera.saveToConfigFile(section+string("_RIGHT"), cfg);

	const CPose3DQuat q = CPose3DQuat(rightCameraPose);
	cfg.write(section+string("_LEFT2RIGHT_POSE"), "pose_quaternion",q.asString() );
}
