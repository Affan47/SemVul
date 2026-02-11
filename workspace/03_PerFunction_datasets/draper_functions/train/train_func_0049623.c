PacketRRMatchesSignature(const CacheRecord *const pktrr, const AuthRecord *const authrr)
	{
	if (!pktrr)  { LogMsg("PacketRRMatchesSignature ERROR: pktrr is NULL"); return(mDNSfalse); }
	if (!authrr) { LogMsg("PacketRRMatchesSignature ERROR: authrr is NULL"); return(mDNSfalse); }
	if (pktrr->resrec.InterfaceID &&
		authrr->resrec.InterfaceID &&
		pktrr->resrec.InterfaceID != authrr->resrec.InterfaceID) return(mDNSfalse);
	if (authrr->resrec.RecordType != kDNSRecordTypeUnique && pktrr->resrec.rrtype != authrr->resrec.rrtype) return(mDNSfalse);
	return(mDNSBool)(pktrr->resrec.rrclass == authrr->resrec.rrclass && pktrr->resrec.namehash == authrr->resrec.namehash && SameDomainName(&pktrr->resrec.name, &authrr->resrec.name));
	}
