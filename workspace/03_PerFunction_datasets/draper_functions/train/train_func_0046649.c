doProcess()
{

	gps.doProcess();


	{
		TListObservations lst;
		gps.getObservations(lst);

		std::vector<mrpt::utils::CSerializablePtr> vect;
		vect.reserve(lst.size());
		for (TListObservations::const_iterator it=lst.begin();it!=lst.end();++it)
			vect.push_back( it->second );
		this->appendObservations(vect);
	}


	std::string sLastGGA = gps.getLastGGA();
	if (!sLastGGA.empty())
	{
		if (m_verbose) cout << "[CGPS_NTRIP] Redirecting GGA frame from GPS->NTRIP: '" << sLastGGA << "'" << endl;

		ntrip.getNTRIPClient().sendBackToServer( sLastGGA + std::string("\r\n") );
	}


	ntrip.doProcess();
}
