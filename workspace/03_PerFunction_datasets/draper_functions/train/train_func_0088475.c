DiscardDeregistrations(mDNS *const m)
	{
	if (m->CurrentRecord) LogMsg("DiscardDeregistrations ERROR m->CurrentRecord already set");
	m->CurrentRecord = m->ResourceRecords;

	while (m->CurrentRecord)
		{
		AuthRecord *rr = m->CurrentRecord;
		m->CurrentRecord = rr->next;
		if (rr->resrec.RecordType == kDNSRecordTypeDeregistering)
			CompleteDeregistration(m, rr);
		}
	}
