UpdateFile(const CServer &server, const CServerPath &path, const wxString& filename, bool mayCreate, enum Filetype type , wxLongLong size )
{
	tServerIter sit = GetServerEntry(server);
	if (sit == m_serverList.end())
		return false;

	bool updated = false;

	for (tCacheIter iter = sit->cacheList.begin(); iter != sit->cacheList.end(); ++iter)
	{
		CCacheEntry &entry = *iter;
		const CCacheEntry &cEntry = *iter;
		if (path.CmpNoCase(entry.listing.path))
			continue;

		UpdateLru(sit, iter);

		bool matchCase = false;
		unsigned int i;
		for (i = 0; i < entry.listing.GetCount(); i++)
		{
			if (!filename.CmpNoCase(cEntry.listing[i].name))
			{
				entry.listing[i].flags |= CDirentry::flag_unsure;
				if (cEntry.listing[i].name == filename)
				{
					matchCase = true;
					break;
				}
			}
		}

		if (matchCase)
		{
			enum Filetype old_type = entry.listing[i].is_dir() ? dir : file;
			if (type != old_type)
				entry.listing.m_hasUnsureEntries |= CDirectoryListing::unsure_invalid;
			else if (type == dir)
				entry.listing.m_hasUnsureEntries |= CDirectoryListing::unsure_dir_changed;
			else
				entry.listing.m_hasUnsureEntries |= CDirectoryListing::unsure_file_changed;
		}
		else if (type != unknown && mayCreate)
		{
			const unsigned int count = entry.listing.GetCount();
			entry.listing.SetCount(count + 1);
			CDirentry& direntry = entry.listing[count];
			direntry.name = filename;
			if (type == dir)
				direntry.flags = CDirentry::flag_dir | CDirentry::flag_unsure;
			else
				direntry.flags = CDirentry::flag_unsure;
			direntry.size = size;
			switch (type)
			{
			case dir:
				entry.listing.m_hasUnsureEntries |= CDirectoryListing::unsure_dir_added;
				break;
			case file:
				entry.listing.m_hasUnsureEntries |= CDirectoryListing::unsure_file_added;
				break;
			default:
				entry.listing.m_hasUnsureEntries |= CDirectoryListing::unsure_invalid;
				break;
			}

			++m_totalFileCount;
		}
		else
			entry.listing.m_hasUnsureEntries |= CDirectoryListing::unsure_unknown;
		entry.modificationTime = CTimeEx::Now();

		updated = true;
	}

	return updated;
}
