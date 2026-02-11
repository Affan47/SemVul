GetTSGroup(std::vector<const TimeSequence*>& tsgroup, const char* groupname) const
	{
		size_t numts = TimeSequences.NumElements();
		for (size_t i = 0; i < numts; i++)
		{
			const TimeSequence& ts = TimeSequences[i];
			if (ts.Group.Value().compare(groupname) == 0)
				tsgroup.push_back(&ts);
		}
	}
