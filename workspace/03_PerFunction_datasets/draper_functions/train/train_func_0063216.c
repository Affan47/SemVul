RWConflictExists(const SERIALIZABLEXACT *reader, const SERIALIZABLEXACT *writer)
{
	RWConflict	conflict;

	Assert(reader != writer);


	if (SxactIsDoomed(reader)
		|| SxactIsDoomed(writer)
		|| SHMQueueEmpty(&reader->outConflicts)
		|| SHMQueueEmpty(&writer->inConflicts))
		return false;


	conflict = (RWConflict)
		SHMQueueNext(&reader->outConflicts,
					 &reader->outConflicts,
					 offsetof(RWConflictData, outLink));
	while (conflict)
	{
		if (conflict->sxactIn == writer)
			return true;
		conflict = (RWConflict)
			SHMQueueNext(&reader->outConflicts,
						 &conflict->outLink,
						 offsetof(RWConflictData, outLink));
	}


	return false;
}
