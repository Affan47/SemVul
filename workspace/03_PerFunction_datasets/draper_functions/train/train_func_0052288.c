ResourceRecordAnswersQuestion(const ResourceRecord *const rr, const DNSQuestion *const q)
	{
	if (rr->InterfaceID &&
		q ->InterfaceID &&
		rr->InterfaceID != q->InterfaceID) return(mDNSfalse);


	if (rr->rrtype != kDNSType_CNAME && rr->rrtype  != q->qtype  && q->qtype  != kDNSQType_ANY ) return(mDNSfalse);
	if (                                rr->rrclass != q->qclass && q->qclass != kDNSQClass_ANY) return(mDNSfalse);
	return(rr->namehash == q->qnamehash && SameDomainName(&rr->name, &q->qname));
	}
