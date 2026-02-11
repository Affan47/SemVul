unloadAutoDetected(void)
{
	std::vector<list<svutTestCase *>::iterator> toRemove;


	for (list<svutTestCase *>::iterator it=suites.begin() ; it != suites.end() ; ++it)
		if ((*it)->isAutodetected())
			toRemove.push_back(it);


	for (std::vector<list<svutTestCase *>::iterator>::iterator it = toRemove.begin() ; it != toRemove.end() ; ++it)
	{
		delete **it;
		suites.erase(*it);
	}
}
