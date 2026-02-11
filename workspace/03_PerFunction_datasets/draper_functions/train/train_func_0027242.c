SetNextCacheCheckTime(mDNS *const m, CacheRecord *const rr)
	{
	rr->NextRequiredQuery = RRExpireTime(rr);


	if (rr->CRActiveQuestion && rr->UnansweredQueries < MaxUnansweredQueries)
		{
		rr->NextRequiredQuery -= TicksTTL(rr)/20 * (MaxUnansweredQueries - rr->UnansweredQueries);
		rr->NextRequiredQuery += mDNSRandom((mDNSu32)TicksTTL(rr)/50);
		verbosedebugf("SetNextCacheCheckTime: %##s (%s) NextRequiredQuery in %ld sec",
			rr->resrec.name.c, DNSTypeName(rr->resrec.rrtype), (rr->NextRequiredQuery - m->timenow) / mDNSPlatformOneSecond);
		}

	if (m->NextCacheCheck - (rr->NextRequiredQuery + CacheCheckGracePeriod(rr)) > 0)
		m->NextCacheCheck = (rr->NextRequiredQuery + CacheCheckGracePeriod(rr));
	}
