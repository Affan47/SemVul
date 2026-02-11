ReconfigureAllProcessings()
	{
		ProcessingsMap::iterator it;
		for( it=_processings.begin(); it!=_processings.end(); it++)
		{
			Processing* proc = it->second;
			proc->Configure( proc->GetConfig() );
		}
	}
