RegisterRelcacheInvalidation(Oid dbId, Oid relId)
{
	AddRelcacheInvalidationMessage(&transInvalInfo->CurrentCmdInvalidMsgs,
								   dbId, relId);


	(void) GetCurrentCommandId(true);


	if (RelationIdIsInInitFile(relId))
		transInvalInfo->RelcacheInitFileInval = true;
}
