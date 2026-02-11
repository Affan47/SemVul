New(const TimeRange& tr, BinMemFactory& memfactory) const
	{
		TimeSequence* ts = new TimeSequence;
		ts->Allocate(layout, tr, memfactory);
		return ts;
	}
