SameRData(const ResourceRecord *const r1, const ResourceRecord *const r2)
	{
	if (r1->rrtype     != r2->rrtype)   return(mDNSfalse);
	if (r1->rdlength   != r2->rdlength) return(mDNSfalse);
	if (r1->rdatahash  != r2->rdatahash) return(mDNSfalse);
	if (r1->rdnamehash != r2->rdnamehash) return(mDNSfalse);
	switch(r1->rrtype)
		{
		case kDNSType_CNAME:
		case kDNSType_PTR:	return(SameDomainName(&r1->rdata->u.name, &r2->rdata->u.name));

		case kDNSType_SRV:	return(mDNSBool)(  	r1->rdata->u.srv.priority          == r2->rdata->u.srv.priority          &&
												r1->rdata->u.srv.weight            == r2->rdata->u.srv.weight            &&
												r1->rdata->u.srv.port.NotAnInteger == r2->rdata->u.srv.port.NotAnInteger &&
												SameDomainName(&r1->rdata->u.srv.target, &r2->rdata->u.srv.target)       );

		default:			return(mDNSPlatformMemSame(r1->rdata->u.data, r2->rdata->u.data, r1->rdlength));
		}
	}
