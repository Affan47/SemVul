ReLoad()
{
	CLAM::ProcessingFactory& factory = CLAM::ProcessingFactory::GetInstance();
	std::list<std::string> usedLibraries=GetUsedLibraries();
	std::list<std::string>::const_iterator itLibraries;

	for (itLibraries=usedLibraries.begin();itLibraries!=usedLibraries.end();itLibraries++)
	{
		CLAM::ProcessingFactory::Keys keys;
		keys=factory.GetKeys("library",(*itLibraries));
		CLAM::ProcessingFactory::Keys::const_iterator itKeys;

		for(itKeys=keys.begin();itKeys!=keys.end();itKeys++)
		{
			factory.DeleteCreator(*itKeys);
		}
		if (needReleaseHandlerOnReload())
		{
			void * handle=GetLibraryHandler(*itLibraries);
			ReleaseLibraryHandler(handle,(*itLibraries));
		}
	}
	Load();
}
