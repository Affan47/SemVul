SkipDB_at_(SkipDB *self, Datum k)
{
	SkipDBRecord *r;

	SkipDB_clearUpdate(self);

	r = SkipDBRecord_find_quick_(self->header, k, 1);


	if (r)
	{
		return Datum_FromUArray_(SkipDBRecord_value(r));
	}

	return Datum_Empty();
}
