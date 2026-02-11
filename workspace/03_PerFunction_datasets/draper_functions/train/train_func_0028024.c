comp_training_lines_by_born_on_date(const void *m1, const void *m2)
{
	int *e1, *e2;
	e1 = (int*) m1;
	e2 = (int*) m2;

	Assert(Mission_events[*e1 & 0xffff].born_on_date != 0);
	Assert(Mission_events[*e2 & 0xffff].born_on_date != 0);

	return (Mission_events[*e1 & 0xffff].born_on_date - Mission_events[*e2 & 0xffff].born_on_date);
}
