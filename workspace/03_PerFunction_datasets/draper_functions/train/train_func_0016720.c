update_object_when(const struct object *o)
{
	struct objcore *oc;
	double when, w2;

	CHECK_OBJ_NOTNULL(o, OBJECT_MAGIC);
	oc = o->objcore;
	CHECK_OBJ_NOTNULL(oc, OBJCORE_MAGIC);
	Lck_AssertHeld(&exp_mtx);

	when = EXP_Keep(NULL, o);
	w2 = EXP_Grace(NULL, o);
	if (w2 > when)
		when = w2;
	assert(!isnan(when));
	if (when == oc->timer_when)
		return (0);
	oc->timer_when = when;
	return (1);
}
