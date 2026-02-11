sortFunctionsTopologically (std::vector<GlslFunction*>& dst, const std::vector<GlslFunction*>& src)
{
	dst.clear();


	FunctionUseCounts useCounts;
	for (std::vector<GlslFunction*>::const_iterator funcIter = src.begin(); funcIter != src.end(); ++funcIter)
		useCounts[(*funcIter)->getMangledName()] = 0;

	for (std::vector<GlslFunction*>::const_iterator funcIter = src.begin(); funcIter != src.end(); ++funcIter)
	{
		std::set<std::string> calledNames = (*funcIter)->getCalledFunctions();
		for (std::set<std::string>::const_iterator callIter = calledNames.begin(); callIter != calledNames.end(); ++callIter)
			useCounts[*callIter] += 1;
	}

	std::vector<GlslFunction*> liveSet;


	for (std::vector<GlslFunction*>::const_iterator funcIter = src.begin(); funcIter != src.end(); ++funcIter)
	{
		if (useCounts[(*funcIter)->getMangledName()] == 0)
			liveSet.push_back(*funcIter);
	}


	while (!liveSet.empty())
	{
		GlslFunction* curFunction = liveSet.back();
		liveSet.pop_back();

		dst.push_back(curFunction);


		std::set<std::string> calledNames = curFunction->getCalledFunctions();
		for (std::set<std::string>::const_iterator callIter = calledNames.begin(); callIter != calledNames.end(); ++callIter)
		{
			int& useCount = useCounts[*callIter];
			useCount -= 1;
			if (useCount == 0)
			{
				GlslFunction* newLiveFunc = resolveFunctionByMangledName(src, *callIter);
				if (!newLiveFunc)
					return false;
				liveSet.push_back(newLiveFunc);
			}
		}
	}


	return dst.size() == src.size();
}
