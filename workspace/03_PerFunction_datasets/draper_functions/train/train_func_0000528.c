GetRRDisplayString_rdb(mDNS *const m, const ResourceRecord *rr, RDataBody *rd)
	{
	char *ptr = m->MsgBuffer;
	mDNSu32 length = mDNS_snprintf(m->MsgBuffer, 79, "%4d %##s %s ", rr->rdlength, rr->name.c, DNSTypeName(rr->rrtype));
	switch (rr->rrtype)
		{
		case kDNSType_A:	mDNS_snprintf(m->MsgBuffer+length, 79-length, "%.4a", &rd->ip);         break;
		case kDNSType_CNAME:
		case kDNSType_PTR:	mDNS_snprintf(m->MsgBuffer+length, 79-length, "%##s", &rd->name);       break;
		case kDNSType_HINFO:
		case kDNSType_TXT:  mDNS_snprintf(m->MsgBuffer+length, 79-length, "%#s", rd->txt.c);        break;
		case kDNSType_AAAA:	mDNS_snprintf(m->MsgBuffer+length, 79-length, "%.16a", &rd->ipv6);      break;
		case kDNSType_SRV:	mDNS_snprintf(m->MsgBuffer+length, 79-length, "%##s", &rd->srv.target); break;
		default:			mDNS_snprintf(m->MsgBuffer+length, 79-length, "RDLen %d: %s",
								rr->rdlength, rd->data);  break;
		}
	for (ptr = m->MsgBuffer; *ptr; ptr++) if (*ptr < ' ') *ptr='.';
	return(m->MsgBuffer);
	}
