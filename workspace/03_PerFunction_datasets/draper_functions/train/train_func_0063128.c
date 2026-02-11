CompleteProbing(mDNS *const m, AuthRecord *const rr)
	{
	verbosedebugf("Probing for %##s (%s) complete", rr->resrec.name.c, DNSTypeName(rr->resrec.rrtype));
	if (!rr->Acknowledged && rr->RecordCallback)
		{


		rr->Acknowledged = mDNStrue;
		m->mDNS_reentrancy++;
		rr->RecordCallback(m, rr, mStatus_NoError);
		m->mDNS_reentrancy--;
		}
	}
