Do()
{


	ProcessingList pendingSinks(mSinks);
	for (ProcessingList::iterator it=mSources.begin(); it!=mSources.end(); it++ )
	{
		Processing* proc = *it;
		if (proc->CanConsumeAndProduce())
		{

			proc->Do();
		}
		else
		{
			std::cerr << "Warning: some AudioSource was not able to consume incoming audio from the call-back.";
		}
	}
	while (true)
	{
		bool noProcessingRun = true;
		for (ProcessingList::iterator it=mNormalProcessings.begin(); it!=mNormalProcessings.end(); it++)
		{
			Processing* proc = *it;
			if (!proc->CanConsumeAndProduce() )
			{

				continue;
			}

			noProcessingRun = false;
			proc->Do();
		}
		for (ProcessingList::iterator it=pendingSinks.begin(); it!=pendingSinks.end(); )
		{
			Processing* proc = *it;
			if (!proc->CanConsumeAndProduce())
			{
				it++;
				continue;
			}

			proc->Do();
			it = pendingSinks.erase(it);
			noProcessingRun = false;
		}
		if (noProcessingRun && !pendingSinks.empty())
		{
			for (ProcessingList::iterator it=mGenerators.begin(); it!=mGenerators.end(); it++)
			{
				Processing* proc = *it;
				if (!proc->CanConsumeAndProduce() )
				{

					continue;
				}

				noProcessingRun = false;
				proc->Do();
			}
		}
		if (noProcessingRun) break;
	}
	if (!pendingSinks.empty())
		std::cerr << "Warning: " << pendingSinks.size() << " sinks were not fed, so could not send audio to the callback." << std::endl;


}
