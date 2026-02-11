AnswerQuestionWithResourceRecord(mDNS *const m, DNSQuestion *q, CacheRecord *rr, mDNSBool AddRecord)
	{
	verbosedebugf("AnswerQuestionWithResourceRecord:%4lu %s TTL%6lu %##s (%s)",
		q->CurrentAnswers, AddRecord ? "Add" : "Rmv", rr->resrec.rroriginalttl, rr->resrec.name.c, DNSTypeName(rr->resrec.rrtype));

	rr->LastUsed = m->timenow;
	rr->UseCount++;
	if (ActiveQuestion(q) && rr->CRActiveQuestion != q)
		{
		if (!rr->CRActiveQuestion) m->rrcache_active++;
		rr->CRActiveQuestion = q;
		SetNextCacheCheckTime(m, rr);
		}


	m->mDNS_reentrancy++;
	if (q->QuestionCallback)
		q->QuestionCallback(m, q, &rr->resrec, AddRecord);
	m->mDNS_reentrancy--;
	}
