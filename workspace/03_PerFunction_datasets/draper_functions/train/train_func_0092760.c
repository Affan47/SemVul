inv_create(Oid lobjId)
{
	Oid			lobjId_new;


	lobjId_new = LargeObjectCreate(lobjId);


	recordDependencyOnOwner(LargeObjectRelationId,
							lobjId_new, GetUserId());


	InvokeObjectPostCreateHook(LargeObjectRelationId, lobjId_new, 0);


	CommandCounterIncrement();

	return lobjId_new;
}
