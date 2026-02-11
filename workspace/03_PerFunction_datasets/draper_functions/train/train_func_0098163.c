ReceiveSharedInvalidMessages(
					  void (*invalFunction) (SharedInvalidationMessage *msg),
							 void (*resetFunction) (void))
{
#define MAXINVALMSGS 32
	static SharedInvalidationMessage messages[MAXINVALMSGS];


	static volatile int nextmsg = 0;
	static volatile int nummsgs = 0;


	while (nextmsg < nummsgs)
	{
		SharedInvalidationMessage msg = messages[nextmsg++];

		SharedInvalidMessageCounter++;
		invalFunction(&msg);
	}

	do
	{
		int			getResult;

		nextmsg = nummsgs = 0;


		getResult = SIGetDataEntries(messages, MAXINVALMSGS);

		if (getResult < 0)
		{

			elog(DEBUG4, "cache state reset");
			SharedInvalidMessageCounter++;
			resetFunction();
			break;
		}


		nextmsg = 0;
		nummsgs = getResult;

		while (nextmsg < nummsgs)
		{
			SharedInvalidationMessage msg = messages[nextmsg++];

			SharedInvalidMessageCounter++;
			invalFunction(&msg);
		}


	} while (nummsgs == MAXINVALMSGS);


	if (catchupInterruptPending)
	{
		catchupInterruptPending = false;
		elog(DEBUG4, "sinval catchup complete, cleaning queue");
		SICleanupQueue(false, 0);
	}
}
