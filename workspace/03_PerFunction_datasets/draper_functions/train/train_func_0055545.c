processXover(const char *msg)
{
	if (strcmp(msg, ".") == 0)
	{
		doNextXoverRange();
		return;
	}

	string xover=msg;

	string fields[8];

	string::iterator b=xover.begin(), e=xover.end();

	size_t i;

	for (i=0; i<8; i++)
	{
		string::iterator c=b;

		while (c != e)
		{
			if (*c == '\t')
				break;
			c++;
		}

		fields[i]=string(b,c);

		if (c != e)
			c++;
		b=c;
	}

	msgnum_t n=0;
	msgnum_t byte_count=0;
	msgnum_t line_count=0;

	{
		istringstream i(fields[0]);

		i >> n;

		if (i.bad() || i.fail())
			return;
	}

	{
		istringstream i(fields[6]);

		i >> byte_count;

		if (i.bad() || i.fail())
			byte_count=0;
	}

	{
		istringstream i(fields[7]);

		i >> line_count;

		if (i.bad() || i.fail())
			line_count=0;
	}

	if (n < firstMsgNum || n > lastMsgNum || !callbackPtr)
		return;

	mail::envelope env;

	mail::generic::genericBuildEnvelope("Subject", fields[1], env);
	mail::generic::genericBuildEnvelope("From", fields[2], env);
	mail::generic::genericBuildEnvelope("Date", fields[3], env);
	mail::generic::genericBuildEnvelope("Message-ID", fields[4], env);
	mail::generic::genericBuildEnvelope("References", fields[5], env);


	size_t msgNum= n - firstMsgNum + prevUid->first;

	if (attributes & MESSAGESIZE)
		xoverCallback.messageSizeCallback(msgNum, byte_count);

	if (attributes & ARRIVALDATE)
		xoverCallback.messageArrivalDateCallback(msgNum,
							 env.date);

	if (attributes & ENVELOPE)
		xoverCallback.messageEnvelopeCallback(msgNum, env);
}
