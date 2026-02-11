Lookup(tCacheIter &cacheIter, tServerIter &sit, const CServerPath &path, bool allowUnsureEntries, bool& is_outdated)
{
	for (tCacheIter iter = sit->cacheList.begin(); iter != sit->cacheList.end(); ++iter)
	{
		const CCacheEntry &entry = *iter;

		if (entry.listing.path != path)
			continue;

		UpdateLru(sit, iter);

		if (!allowUnsureEntries && entry.listing.m_hasUnsureEntries)
			return false;

		cacheIter = iter;
		is_outdated = (wxDateTime::Now() - entry.listing.m_firstListTime.GetTime()).GetSeconds() > CACHE_TIMEOUT;
		return true;
	}

	return false;
}
