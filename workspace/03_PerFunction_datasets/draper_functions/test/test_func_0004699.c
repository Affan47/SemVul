operator=(const CDirectoryListing &a)
{
	if (&a == this)
		return *this;

	m_entries = a.m_entries;

	path = a.path;

	m_hasUnsureEntries = a.m_hasUnsureEntries;
	m_failed = a.m_failed;

	m_entryCount = a.m_entryCount;

	m_firstListTime = a.m_firstListTime;

	m_hasDirs = a.m_hasDirs;

	m_searchmap_case = a.m_searchmap_case;
	m_searchmap_nocase = a.m_searchmap_nocase;

	m_has_perms = a.m_has_perms;
	m_has_usergroup = a.m_has_usergroup;

	return *this;
}
