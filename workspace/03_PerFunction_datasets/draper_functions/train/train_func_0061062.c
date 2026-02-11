UDBRecords_firstEmptyRecord(UDBRecords *self)
{


	if (self->firstEmptyPos)
	{
		UDBRecord_setPos_(self->firstEmptyRecord, self->firstEmptyPos);

		if (UDBRecord_readHeader(self->firstEmptyRecord))
		{
			return self->firstEmptyRecord;
		}
	}

	return NULL;
}
