loadFromConfigFile(
	const mrpt::utils::CConfigFileBase  &ini,
	const std::string &sectionName )
{
	MRPT_START
	using internal::TMetricMapTypesRegistry;


	clear();

	TMetricMapTypesRegistry & mmr = TMetricMapTypesRegistry::Instance();

	const TMetricMapTypesRegistry::TListRegisteredMaps & allMapKinds = mmr.getAllRegistered();
	for (TMetricMapTypesRegistry::TListRegisteredMaps::const_iterator itMapKind=allMapKinds.begin();itMapKind!=allMapKinds.end();++itMapKind)
	{


		const std::string sMapName = itMapKind->first;

		unsigned int n = ini.read_uint64_t(sectionName,sMapName+string("_count"),0);
		for (unsigned int i=0;i<n;i++)
		{
			TMetricMapInitializer *mi = mmr.factoryMapDefinition(sMapName);
			ASSERT_(mi);


			const string sMapSectionsPrefix = mrpt::format("%s_%s_%02u",sectionName.c_str(),sMapName.c_str(),i);
			mi->loadFromConfigFile(ini,sMapSectionsPrefix);


			this->push_back( TMetricMapInitializerPtr(mi) );
		}

	}

	MRPT_END
}
