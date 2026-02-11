LocateAnswers(const DNSMessage *const msg, const mDNSu8 *const end)
	{
	int i;
	const mDNSu8 *ptr = msg->data;
	for (i = 0; i < msg->h.numQuestions && ptr; i++) ptr = skipQuestion(msg, ptr, end);
	return(ptr);
	}
