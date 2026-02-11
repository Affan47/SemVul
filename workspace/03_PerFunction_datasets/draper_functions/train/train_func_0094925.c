CommandEndInvalidationMessages(void)
{


	if (transInvalInfo == NULL)
		return;

	ProcessInvalidationMessages(&transInvalInfo->CurrentCmdInvalidMsgs,
								LocalExecuteInvalidationMessage);
	AppendInvalidationMessages(&transInvalInfo->PriorCmdInvalidMsgs,
							   &transInvalInfo->CurrentCmdInvalidMsgs);
}
