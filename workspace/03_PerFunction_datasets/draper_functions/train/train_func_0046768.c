ReplaceAliases(GdlRule * prule)
{
	GdlSetAttrItem::ReplaceAliases(prule);

	if (m_pexpSelector)
		m_pexpSelector->ReplaceAliases(prule);

	for (size_t ipexp = 0; ipexp < m_vpexpAssocs.size(); ipexp++)
	{
		m_vpexpAssocs[ipexp]->ReplaceAliases(prule);
	}
}
