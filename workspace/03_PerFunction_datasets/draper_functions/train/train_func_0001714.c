CleanSubId()
{
	FUSUniqueStringMap myStringMap;

	for (FCDPhysicsModelInstanceContainer::iterator it = instances.begin(); it != instances.end(); ++it)
	{
		(*it)->CleanSubId(&myStringMap);
	}
}
