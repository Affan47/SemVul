PrepareInvalidationState(void)
{
	TransInvalidationInfo *myInfo;

	if (transInvalInfo != NULL &&
		transInvalInfo->my_level == GetCurrentTransactionNestLevel())
		return;

	myInfo = (TransInvalidationInfo *)
		MemoryContextAllocZero(TopTransactionContext,
							   sizeof(TransInvalidationInfo));
	myInfo->parent = transInvalInfo;
	myInfo->my_level = GetCurrentTransactionNestLevel();


	Assert(transInvalInfo == NULL ||
		   myInfo->my_level > transInvalInfo->my_level);

	transInvalInfo = myInfo;
}
