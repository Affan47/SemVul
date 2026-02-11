GetRDLength(const ResourceRecord *const rr, mDNSBool estimate)
	{
	RDataBody *rd = &rr->rdata->u;
	const domainname *const name = estimate ? &rr->name : mDNSNULL;
	switch (rr->rrtype)
		{
		case kDNSType_A:	return(sizeof(rd->ip));
		case kDNSType_CNAME:
		case kDNSType_PTR:	return(CompressedDomainNameLength(&rd->name, name));
		case kDNSType_HINFO:return(mDNSu16)(2 + (int)rd->data[0] + (int)rd->data[1 + (int)rd->data[0]]);
		case kDNSType_NULL:
		case kDNSType_TXT:  return(rr->rdlength);
		case kDNSType_AAAA:	return(sizeof(rd->ipv6));
		case kDNSType_SRV:	return(mDNSu16)(6 + CompressedDomainNameLength(&rd->srv.target, name));
		default:			debugf("Warning! Don't know how to get length of resource type %d", rr->rrtype);
							return(rr->rdlength);
		}
	}
