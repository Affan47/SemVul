HaveSentEntireRRSet(const mDNS *const m, const AuthRecord *const rr, mDNSInterfaceID InterfaceID)
	{

	const AuthRecord *a;
	for (a = m->ResourceRecords; a; a=a->next)
		if (a->SendRNow == InterfaceID && a != rr && SameResourceRecordSignature(&a->resrec, &rr->resrec)) break;
	return (a == mDNSNULL);
	}
