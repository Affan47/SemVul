loadFromTextFile(const std::string &filName)
{
	MRPT_START

	BASE::clear();

	ifstream f(filName.c_str());
	if (!f.is_open()) THROW_EXCEPTION_CUSTOM_MSG1("Can't open file: %s",filName.c_str())

	unsigned int linNum = 0;
	while (!f.fail())
	{
		linNum++;
		string lin;
		std::getline(f,lin);
		lin=trim(lin);
		if (lin.empty() || lin[0]=='%') continue;


		std::istringstream s;
		s.str(lin);

		TFeatureID		featID;
		TCameraPoseID  	camID;
		TPixelCoordf	px;
		if (!(s >> camID >> featID >> px.x >> px.y))
			THROW_EXCEPTION(format("%s:%u: Error parsing line: '%s'",filName.c_str(),linNum,lin.c_str()))

		BASE::push_back( TFeatureObservation(featID,camID,px) );
	}

	MRPT_END
}
