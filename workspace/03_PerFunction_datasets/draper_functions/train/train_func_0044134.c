SkipDBRecord_recordAtLevel_(SkipDBRecord *self, int level)
{
	SkipDBRecord_checkLevel_(self, level);

	{
		SkipDBPointer *p = SkipDBRecord_pointerAtLevel_(self, level);
		SkipDBRecord *r = p->record;

		if (!r && p->pid)
		{
			r = SkipDB_recordAtPid_((SkipDB *)(self->sdb), p->pid);
			SkipDBPointer_setRecord_(p, r);
		}

		return r;
	}
}
