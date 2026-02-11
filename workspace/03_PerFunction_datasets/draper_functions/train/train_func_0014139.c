SkipDB_noteDirtyRecord_(SkipDB *self, SkipDBRecord *r)
{
	if (SkipDB_isOpen(self))
	{
		List_append_(self->dirtyRecords, r);
	}
}
