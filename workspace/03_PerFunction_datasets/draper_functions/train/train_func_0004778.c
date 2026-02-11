SkipDB_show(SkipDB *self)
{
	SkipDBRecord *r = self->header;
	printf("\nSkipDB:\n");
	while (r)
	{
		SkipDBRecord_show(r);
		r = SkipDBRecord_recordAtLevel_(r, 0);
	}
	printf("\n\n");
}
