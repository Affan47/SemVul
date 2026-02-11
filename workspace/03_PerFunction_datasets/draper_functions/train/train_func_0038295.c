AnswerNewQuestion(mDNS *const m)
	{
	mDNSBool ShouldQueryImmediately = mDNStrue;
	CacheRecord *rr;
	DNSQuestion *q = m->NewQuestions;
	mDNSu32 slot = HashSlot(&q->qname);

	verbosedebugf("AnswerNewQuestion: Answering %##s (%s)", q->qname.c, DNSTypeName(q->qtype));

	CheckCacheExpiration(m, slot);
	m->NewQuestions = q->next;

	if (m->lock_rrcache) LogMsg("AnswerNewQuestion ERROR! Cache already locked!");


	m->lock_rrcache = 1;
	if (m->CurrentQuestion) LogMsg("AnswerNewQuestion ERROR m->CurrentQuestion already set");
	m->CurrentQuestion = q;
	for (rr=m->rrcache_hash[slot]; rr; rr=rr->next)
		if (ResourceRecordAnswersQuestion(&rr->resrec, q))
			{

			mDNSu32 SecsSinceRcvd = ((mDNSu32)(m->timenow - rr->TimeRcvd)) / mDNSPlatformOneSecond;
			if (rr->resrec.rroriginalttl <= SecsSinceRcvd)
				{
				LogMsg("AnswerNewQuestion: How is rr->resrec.rroriginalttl %lu <= SecsSinceRcvd %lu for %##s (%s)",
					rr->resrec.rroriginalttl, SecsSinceRcvd, rr->resrec.name.c, DNSTypeName(rr->resrec.rrtype));
				continue;
				}


			if (rr->resrec.RecordType & kDNSRecordTypePacketUniqueMask) ShouldQueryImmediately = mDNSfalse;
			q->CurrentAnswers++;
			if (rr->resrec.rdlength > SmallRecordLimit) q->LargeAnswers++;
			if (rr->resrec.RecordType & kDNSRecordTypePacketUniqueMask) q->UniqueAnswers++;
			AnswerQuestionWithResourceRecord(m, q, rr, mDNStrue);

			if (m->CurrentQuestion != q) break;
			}
		else if (RRTypeIsAddressType(rr->resrec.rrtype) && RRTypeIsAddressType(q->qtype))
			if (rr->resrec.namehash == q->qnamehash && SameDomainName(&rr->resrec.name, &q->qname))
				ShouldQueryImmediately = mDNSfalse;

	if (ShouldQueryImmediately && m->CurrentQuestion == q)
		{
		q->ThisQInterval = InitialQuestionInterval;
		q->LastQTime = m->timenow - q->ThisQInterval;
		m->NextScheduledQuery = m->timenow;
		}
	m->CurrentQuestion = mDNSNULL;
	m->lock_rrcache = 0;
	}
