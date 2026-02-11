fromString(const std::string &s)
{
	MRPT_TRY_START

	this->clear();
	std::vector<std::string> lstClasses;
	mrpt::system::tokenize(s," ,",lstClasses);

	for (size_t i=0;i<lstClasses.size();i++)
	{
		const mrpt::utils::TRuntimeClassId* id = mrpt::utils::findRegisteredClass(lstClasses[i]);
		ASSERTMSG_(id!=NULL, format("Unknown class name: %s",lstClasses[i].c_str()))
		this->insert(id);
	}

	MRPT_TRY_END
}
